import string
from copy import deepcopy
from typing import AbstractSet, Iterable, Tuple, Dict, Any

import networkx as nx

from .cfg_object import CFGObject
from .epsilon import Epsilon
from .production import Production
from .terminal import Terminal
from .utils import to_variable, to_terminal
from .utils_cfg import remove_nullable_production, get_productions_d
from .variable import Variable

EPSILON_SYMBOLS = ["_"]

class NotParsableException(Exception):
    """"""


def is_special_text(text):
    return len(text) > 5 and \
        (text[0:5] == '"VAR:' or text[0:5] == '"TER:') and \
        text[-1] == '"'


class CFG:
    def __init__(self,
                 variables: AbstractSet[Variable] = None,
                 terminals: AbstractSet[Terminal] = None,
                 start_symbol: Variable = None,
                 productions: Iterable[Production] = None):
        if variables is not None:
            variables = {to_variable(x) for x in variables}
        self._variables = variables or set()
        self._variables = set(self._variables)
        if terminals is not None:
            terminals = {to_terminal(x) for x in terminals}
        self._terminals = terminals or set()
        self._terminals = set(self._terminals)
        if start_symbol is not None:
            start_symbol = to_variable(start_symbol)
        self._start_symbol = start_symbol
        if start_symbol is not None:
            self._variables.add(start_symbol)
        self._productions = productions or set()
        self._productions = self._productions
        for production in self._productions:
            self.__initialize_production_in_cfg(production)
        self._normal_form = None
        self._generating_symbols = None
        self._nullable_symbols = None
        self._impacts = None
        self._remaining_lists = None
        self._added_impacts = None

    def __initialize_production_in_cfg(self, production):
        self._variables.add(production.head)
        for cfg_object in production.body:
            if isinstance(cfg_object, Terminal):
                self._terminals.add(cfg_object)
            else:
                self._variables.add(cfg_object)

    def get_generating_symbols(self) -> AbstractSet[CFGObject]:
        if self._generating_symbols is None:
            self._generating_symbols = self._get_generating_or_nullable(False)
        return self._generating_symbols

    def _get_generating_or_nullable(self, nullable=False):
        """ Merge of nullable and generating """
        to_process = [Epsilon()]
        g_symbols = {Epsilon()}

        self._set_impacts_and_remaining_lists()

        for symbol in self._added_impacts:
            if symbol not in g_symbols:
                g_symbols.add(symbol)
                to_process.append(symbol)

        if not nullable:
            for terminal in self._terminals:
                g_symbols.add(terminal)
                to_process.append(terminal)

        processed_with_modification = []
        while to_process:
            current = to_process.pop()
            for symbol_impact, index_impact in self._impacts.get(current, []):
                if symbol_impact in g_symbols:
                    continue
                processed_with_modification.append(
                    (symbol_impact, index_impact))
                self._remaining_lists[symbol_impact][index_impact] -= 1
                if self._remaining_lists[symbol_impact][index_impact] == 0:
                    g_symbols.add(symbol_impact)
                    to_process.append(symbol_impact)
        # Fix modifications
        for symbol_impact, index_impact in processed_with_modification:
            self._remaining_lists[symbol_impact][index_impact] += 1
        g_symbols.remove(Epsilon())
        return g_symbols

    def _set_impacts_and_remaining_lists(self):
        if self._impacts is not None:
            return
        self._added_impacts = set()
        self._remaining_lists = {}
        self._impacts = {}
        for production in self._productions:
            head = production.head  # Should check if head is not Epsilon?
            body = production.body
            if not body:
                self._added_impacts.add(head)
                continue
            temp = self._remaining_lists.setdefault(head, [])
            temp.append(len(body))
            index_impact = len(temp) - 1
            for symbol in body:
                self._impacts.setdefault(symbol, []).append(
                    (head, index_impact))


    def get_reachable_symbols(self) -> AbstractSet[CFGObject]:
        r_symbols = set()
        r_symbols.add(self._start_symbol)
        reachable_transition_d = {}
        for production in self._productions:
            temp = reachable_transition_d.setdefault(production.head, [])
            for symbol in production.body:
                if not isinstance(symbol, Epsilon):
                    temp.append(symbol)
        to_process = [self._start_symbol]
        while to_process:
            current = to_process.pop()
            for next_symbol in reachable_transition_d.get(current, []):
                if next_symbol not in r_symbols:
                    r_symbols.add(next_symbol)
                    to_process.append(next_symbol)
        return r_symbols

    def remove_useless_symbols(self) -> "CFG":
        generating = self.get_generating_symbols()
        productions = [x for x in self._productions
                       if x.head in generating and
                       all(y in generating for y in x.body)]
        new_var = self._variables.intersection(generating)
        new_ter = self._terminals.intersection(generating)
        cfg_temp = CFG(new_var, new_ter, self._start_symbol, productions)
        reachables = cfg_temp.get_reachable_symbols()
        productions = [x for x in productions
                       if x.head in reachables]
        new_var = new_var.intersection(reachables)
        new_ter = new_ter.intersection(reachables)
        return CFG(new_var, new_ter, self._start_symbol, productions)


    def get_nullable_symbols(self) -> AbstractSet[CFGObject]:
        if self._nullable_symbols is None:
            self._nullable_symbols = self._get_generating_or_nullable(True)
        return self._nullable_symbols

    def remove_epsilon(self) -> "CFG":
        new_productions = []
        nullables = self.get_nullable_symbols()
        for production in self._productions:
            new_productions += remove_nullable_production(production,
                                                          nullables)
        return CFG(self._variables,
                   self._terminals,
                   self._start_symbol,
                   new_productions)

    def get_unit_pairs(self) -> AbstractSet[Tuple[Variable, Variable]]:
        unit_pairs = set()
        for variable in self._variables:
            unit_pairs.add((variable, variable))
        productions = [x
                       for x in self._productions
                       if len(x.body) == 1 and isinstance(x.body[0], Variable)]
        productions_d = get_productions_d(productions)
        to_process = list(unit_pairs)
        while to_process:
            var_a, var_b = to_process.pop()
            for production in productions_d.get(var_b, []):
                temp = (var_a, production.body[0])
                if temp not in unit_pairs:
                    unit_pairs.add(temp)
                    to_process.append(temp)
        return unit_pairs


    def eliminate_unit_productions(self) -> "CFG":
        unit_pairs = self.get_unit_pairs()
        productions = [x
                       for x in self._productions
                       if len(x.body) != 1
                       or not isinstance(x.body[0], Variable)]
        productions_d = get_productions_d(productions)
        for var_a, var_b in unit_pairs:
            for production in productions_d.get(var_b, []):
                productions.append(Production(var_a, production.body,
                                              filtering=False))
        return CFG(self._variables,
                   self._terminals,
                   self._start_symbol,
                   productions)


    def _get_productions_with_only_single_terminals(self):
        term_to_var = {}
        new_productions = []
        for terminal in self._terminals:
            var = Variable(str(terminal.value) + "#CNF#")
            term_to_var[terminal] = var
        used = set()
        for production in self._productions:
            if len(production.body) == 1:
                new_productions.append(production)
                continue
            new_body = []
            for symbol in production.body:
                if symbol in term_to_var:
                    new_body.append(term_to_var[symbol])
                    used.add(symbol)
                else:
                    new_body.append(symbol)
            new_productions.append(Production(production.head,
                                              new_body))
        for terminal in used:
            new_productions.append(
                Production(term_to_var[terminal], [terminal]))
        return new_productions

    def _get_next_free_variable(self, idx, prefix):
        idx += 1
        temp = Variable(prefix + str(idx))
        while temp in self._variables:
            idx += 1
            temp = Variable(prefix + str(idx))
        return idx, temp

    def _decompose_productions(self, productions):
        idx = 0
        new_productions = []
        done = {}
        for production in productions:
            body = production.body
            if len(body) <= 2:
                new_productions.append(production)
                continue
            new_var = []
            for _ in range(len(body) - 2):
                idx, var = self._get_next_free_variable(idx, "C#CNF#")
                new_var.append(var)
            head = production.head
            stopped = False
            for i in range(len(body) - 2):
                temp = tuple(body[i + 1:])
                if temp in done:
                    new_productions.append(Production(head,
                                                      [body[i], done[temp]]))
                    stopped = True
                    break
                new_productions.append(Production(head, [body[i], new_var[i]]))
                done[temp] = new_var[i]
                head = new_var[i]
            if not stopped:
                new_productions.append(Production(head, [body[-2], body[-1]]))
        return new_productions

    def to_normal_form(self) -> "CFG":
        if self._normal_form is not None:
            return self._normal_form
        nullables = self.get_nullable_symbols()
        unit_pairs = self.get_unit_pairs()
        generating = self.get_generating_symbols()
        reachables = self.get_reachable_symbols()
        if (len(nullables) != 0 or len(unit_pairs) != len(self._variables) or
                len(generating) !=
                len(self._variables) + len(self._terminals) or
                len(reachables) !=
                len(self._variables) + len(self._terminals)):
            if len(self._productions) == 0:
                self._normal_form = self
                return self
            new_cfg = self.remove_useless_symbols() \
                .remove_epsilon() \
                .remove_useless_symbols() \
                .eliminate_unit_productions() \
                .remove_useless_symbols()
            cfg = new_cfg.to_normal_form()
            self._normal_form = cfg
            return cfg
        # Remove terminals from body
        new_productions = self._get_productions_with_only_single_terminals()
        new_productions = self._decompose_productions(new_productions)
        cfg = CFG(start_symbol=self._start_symbol,
                  productions=set(new_productions))
        self._normal_form = cfg
        return cfg

    @property
    def variables(self) -> AbstractSet[Variable]:
        return self._variables

    @property
    def terminals(self) -> AbstractSet[Terminal]:
        return self._terminals

    @property
    def productions(self) -> AbstractSet[Production]:
        return self._productions

    @property
    def start_symbol(self) -> Variable:
        return self._start_symbol


    def get_words(self, max_length: int = -1):
        nullables = self.get_nullable_symbols()
        if self.start_symbol in nullables:
            yield []
        if max_length == 0:
            return
        cfg = self.to_normal_form()
        productions = cfg.productions
        gen_d = {}

        for production in productions:
            if production.head not in gen_d:
                gen_d[production.head] = [[]]
            if len(production.body) == 2:
                for obj in production.body:
                    if obj not in gen_d:
                        gen_d[obj] = [[]]

        for production in productions:
            body = production.body
            if len(body) == 1:
                if len(gen_d[production.head]) == 1:
                    gen_d[production.head].append([])
                if body not in gen_d[production.head][-1]:
                    gen_d[production.head][-1].append(list(body))
                    if production.head == cfg.start_symbol:
                        yield list(body)

        current_length = 2
        total_no_modification = 0
        while current_length <= max_length or max_length == -1:
            was_modified = False
            for gen in gen_d.values():
                if len(gen) != current_length:
                    gen.append([])
            for production in productions:
                body = production.body
                if len(gen_d[production.head]) != current_length + 1:
                    gen_d[production.head].append([])
                if len(body) != 2:
                    continue
                for i in range(1, current_length):
                    j = current_length - i
                    for left in gen_d[body[0]][i]:
                        for right in gen_d[body[1]][j]:
                            new_word = left + right
                            if new_word not in gen_d[production.head][-1]:
                                was_modified = True
                                gen_d[production.head][-1].append(new_word)
                                if production.head == cfg.start_symbol:
                                    yield new_word
            if was_modified:
                total_no_modification = 0
            else:
                total_no_modification += 1
            current_length += 1
            if total_no_modification > current_length / 2:
                return


    def to_text(self):
        res = []
        for production in self._productions:
            res.append(str(production.head) + " -> " +
                       " ".join([x.to_text() for x in production.body]))
        return "\n".join(res) + "\n"
