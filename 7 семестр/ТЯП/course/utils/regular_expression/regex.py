import random
from typing import Iterable
from utils.cfg.cfg import CFG
from utils import cfg
from utils.regular_expression.regex_reader import RegexReader

class Regex(RegexReader):

    def __init__(self, regex):
        self.head = None
        self.sons = None
        super().__init__(regex)
        self._counter = 0
        self._regex = self._regex.replace(" ", "")
        print(self._regex)


    def to_cfg(self, starting_symbol="S") -> CFG:
        productions, _ = self._get_production(starting_symbol)
        cfg_res = cfg.CFG(start_symbol=cfg.utils.to_variable(starting_symbol),
                          productions=set(productions))
        return cfg_res


    def _get_production(self, current_symbol, count=0):
        next_symbols = []
        next_productions = []
        for son in self.sons:
            next_symbol = "A" + str(count)
            count += 1
            new_prods, count = son._get_production(next_symbol, count)
            next_symbols.append(next_symbol)
            next_productions += new_prods
        new_prods = self.head.get_cfg_rules(current_symbol, next_symbols)
        next_productions += new_prods
        return next_productions, count


    def __repr__(self):
        return self.head.get_str_repr([str(son) for son in self.sons])


    def from_string(self, regex_str: str):
        return Regex(regex_str)


    def generate_words(self, min_length, max_length):
        range_1 = min_length
        range_2 = max_length
        reg_ex_chain = self._regex
        split_chain = []
        service_symbols = []
        counter = 0
        start_position = 0
        sym_num = 0
        while sym_num < len(reg_ex_chain):
            if reg_ex_chain[sym_num] == '(':
                counter += 1
            elif reg_ex_chain[sym_num] == ')':
                counter -= 1
            if counter == 0:
                if sym_num == len(reg_ex_chain) - 1 or reg_ex_chain[sym_num+1] == '(' or reg_ex_chain[sym_num+1] == '+' or reg_ex_chain[sym_num+1] == '*' or reg_ex_chain[sym_num+1] == '⁺':
                    if reg_ex_chain[start_position] != '(':
                        split_chain.append([[reg_ex_chain[start_position:sym_num+1]]])
                    else:
                        split_chain.append([[reg_ex_chain[(start_position+1):sym_num]]])
                    if sym_num == len(reg_ex_chain) - 1:
                        service_symbols.append([['-']])
                        start_position = sym_num + 1
                    elif reg_ex_chain[sym_num+1] == '(':
                        service_symbols.append([['-']])
                        start_position = sym_num + 1
                    elif reg_ex_chain[sym_num+1] == '+':
                        service_symbols.append([['+']])
                        sym_num += 1
                        start_position = sym_num + 1
                    elif reg_ex_chain[sym_num+1] == '*':
                        if sym_num == len(reg_ex_chain) - 2:
                            service_symbols.append([['*']])
                            sym_num += 1
                            start_position = sym_num + 1
                        elif reg_ex_chain[sym_num+2] != '+':
                            service_symbols.append([['*']])
                            sym_num += 1
                            start_position = sym_num + 1
                        else:
                            service_symbols.append([['*+']])
                            sym_num += 2
                            start_position = sym_num + 1
                    elif reg_ex_chain[sym_num+1] == '⁺':
                        if sym_num == len(reg_ex_chain) - 2:
                            service_symbols.append([['⁺']])
                            sym_num += 1
                            start_position = sym_num + 1
                        elif reg_ex_chain[sym_num+2] != '+':
                            service_symbols.append([['⁺']])
                            sym_num += 1
                            start_position = sym_num + 1
                        else:
                            service_symbols.append([['⁺+']])
                            sym_num += 2
                            start_position = sym_num + 1
                    else:
                        raise 'Error'
            sym_num += 1
        def split_reg_ex(service_symbols_rec, split_chain_rec):
            for ss_num in range(0,len(service_symbols_rec)):
                if service_symbols_rec[ss_num][0][0] != '-':
                    split_chain_rec[ss_num].append([])
                    service_symbols_rec[ss_num].append([])
                    counter = 0
                    start_position = 0
                    sym_num = 0
                    while sym_num < len(split_chain_rec[ss_num][0][0]):
                        if split_chain_rec[ss_num][0][0][sym_num] == '(':
                            counter += 1
                        elif split_chain_rec[ss_num][0][0][sym_num] == ')':
                            counter -= 1
                        if counter == 0:
                            if sym_num == len(split_chain_rec[ss_num][0][0]) - 1 or split_chain_rec[ss_num][0][0][sym_num+1] == '(' or split_chain_rec[ss_num][0][0][sym_num+1] == '+' or split_chain_rec[ss_num][0][0][sym_num+1] == '*' or split_chain_rec[ss_num][0][0][sym_num+1] == '⁺':
                                if split_chain_rec[ss_num][0][0][start_position] != '(':
                                    split_chain_rec[ss_num][1].append([[split_chain_rec[ss_num][0][0][start_position:sym_num+1]]])
                                else:
                                    split_chain_rec[ss_num][1].append([[split_chain_rec[ss_num][0][0][(start_position+1):sym_num]]])
                                if sym_num == len(split_chain_rec[ss_num][0][0]) - 1:
                                    service_symbols_rec[ss_num][1].append([['-']])
                                    start_position = sym_num + 1
                                elif split_chain_rec[ss_num][0][0][sym_num+1] == '(':
                                    service_symbols_rec[ss_num][1].append([['-']])
                                    start_position = sym_num + 1
                                elif split_chain_rec[ss_num][0][0][sym_num+1] == '+':
                                    service_symbols_rec[ss_num][1].append([['+']])
                                    sym_num += 1
                                    start_position = sym_num + 1
                                elif split_chain_rec[ss_num][0][0][sym_num+1] == '*':
                                    if sym_num == len(split_chain_rec[ss_num][0][0]) - 2:
                                        service_symbols_rec[ss_num][1].append([['*']])
                                        sym_num += 1
                                        start_position = sym_num + 1
                                    elif split_chain_rec[ss_num][0][0][sym_num+2] != '+':
                                        service_symbols_rec[ss_num][1].append([['*']])
                                        sym_num += 1
                                        start_position = sym_num + 1
                                    else:
                                        service_symbols_rec[ss_num][1].append([['*+']])
                                        sym_num += 2
                                        start_position = sym_num + 1
                                elif split_chain_rec[ss_num][0][0][sym_num+1] == '⁺':
                                    if sym_num == len(split_chain_rec[ss_num][0][0]) - 2:
                                        service_symbols_rec[ss_num][1].append([['⁺']])
                                        sym_num += 1
                                        start_position = sym_num + 1
                                    elif split_chain_rec[ss_num][0][0][sym_num+2] != '+':
                                        service_symbols_rec[ss_num][1].append([['⁺']])
                                        sym_num += 1
                                        start_position = sym_num + 1
                                    else:
                                        service_symbols_rec[ss_num][1].append([['⁺+']])
                                        sym_num += 2
                                        start_position = sym_num + 1
                                else:
                                    raise 'Error'
                        sym_num += 1
                    split_reg_ex(service_symbols_rec[ss_num][1], split_chain_rec[ss_num][1])

        split_reg_ex(service_symbols, split_chain)
        def generate_chains(service_symbols_rec, split_chain_rec, range_1, range_2, level = 0, cnt = 0):
            chains = ['']
            is_pluses = False
            ss_num = 0
            for a in service_symbols_rec:
                if a[0][0] == '+' or a[0][0] == '-':
                    cnt += 1
            while ss_num < len(service_symbols_rec):
                if service_symbols_rec[ss_num][0][0] == '-':
                    buf = split_chain_rec[ss_num][0][0].split('+')
                elif service_symbols_rec[ss_num][0][0] == '+':
                    buf = split_chain_rec[ss_num][0][0].split('+')
                    is_pluses = True
                elif service_symbols_rec[ss_num][0][0] == '⁺':
                    buf = generate_chains(service_symbols_rec[ss_num][1], split_chain_rec[ss_num][1], range_1, range_2, level+1, cnt)
                    size = len(buf)
                    size_2 = len(buf)
                    start_pos = 0
                    is_next = True
                    while is_next:
                        is_next = False
                        for b_num in range(0, size):
                            for b_num_2 in range(start_pos, size_2):
                                if len(buf[b_num]+buf[b_num_2]) <= range_2:
                                    buf.append(buf[b_num]+buf[b_num_2])
                                    is_next = True
                        start_pos = size_2-1
                        size_2 = len(buf) - size_2
                elif service_symbols_rec[ss_num][0][0] == '*':
                    buf = generate_chains(service_symbols_rec[ss_num][1], split_chain_rec[ss_num][1], range_1, range_2, level+1, cnt)
                    size = len(buf)
                    size_2 = len(buf)
                    start_pos = 0
                    is_next = True
                    while is_next:
                        is_next = False
                        for b_num in range(0, size):
                            for b_num_2 in range(start_pos, size_2):
                                if len(buf[b_num]+buf[b_num_2]) <= range_2:
                                    buf.append(buf[b_num]+buf[b_num_2])
                                    is_next = True
                        start_pos = size_2-1
                        size_2 = len(buf) - size_2
                    buf.append('')
                    buf_3 = []
                    if len(service_symbols_rec)-1 > ss_num:
                        if service_symbols_rec[ss_num+1][0][0] == '+':
                            buf_2 = split_chain_rec[ss_num+1][0][0].split('+')
                            is_pluses = True
                            for buf_num in range(0,len(buf)):
                                for buf_2_num in range(0,len(buf_2)):
                                    buf_3.append(buf[buf_num]+buf_2[buf_2_num])
                            buf = buf_3
                            ss_num += 1
                        elif service_symbols_rec[ss_num+1][0][0] == '-':
                            buf_2 = split_chain_rec[ss_num+1][0][0].split('+')

                            for buf_num in range(0,len(buf)):
                                for buf_2_num in range(0,len(buf_2)):
                                    buf_3.append(buf[buf_num]+buf_2[buf_2_num])
                            buf = buf_3
                            ss_num += 1
                elif service_symbols_rec[ss_num][0][0] == '*+':
                    buf = generate_chains(service_symbols_rec[ss_num][1], split_chain_rec[ss_num][1], range_1, range_2, level+1, cnt)
                    size = len(buf)
                    size_2 = len(buf)
                    start_pos = 0
                    is_next = True
                    while is_next:
                        is_next = False
                        for b_num in range(0, size):
                            for b_num_2 in range(start_pos, size_2):
                                if len(buf[b_num]+buf[b_num_2]) <= range_2:
                                    buf.append(buf[b_num]+buf[b_num_2])
                                    is_next = True
                        start_pos = size_2-1
                        size_2 = len(buf) - size_2
                    buf.append('')
                    is_pluses = True
                elif service_symbols_rec[ss_num][0][0] == '⁺+':
                    buf = generate_chains(service_symbols_rec[ss_num][1], split_chain_rec[ss_num][1], range_1, range_2, level+1, cnt)
                    size = len(buf)
                    size_2 = len(buf)
                    start_pos = 0
                    is_next = True
                    while is_next:
                        is_next = False
                        for b_num in range(0, size):
                            for b_num_2 in range(start_pos, size_2):
                                if len(buf[b_num]+buf[b_num_2]) <= range_2:
                                    buf.append(buf[b_num]+buf[b_num_2])
                                    is_next = True
                        start_pos = size_2-1
                        size_2 = len(buf) - size_2
                    is_pluses = True
                if not is_pluses:
                    counter = len(chains)
                    while counter != 0:
                        for elem in buf:
                            if len(chains[0]+elem) <= range_2:
                                chains.append(chains[0]+elem)
                        chains.pop(0)
                        counter -= 1
                else:
                    for elem in buf:
                        chains.append(chains[0]+elem)
                ss_num += 1
            if is_pluses:
                chains.pop(0)
            chains_set = set(chains)
            chain_list = []
            if level == 0:
                for chain in list(chains_set):
                    if len(chain) >= range_1 and len(chain) <= range_2:
                        chain_list.append(chain)
            else:
                for chain in list(chains_set):
                    if len(chain) <= range_2:
                        chain_list.append(chain)
            return(chain_list)

        resulting_chains = generate_chains(service_symbols, split_chain, range_1, range_2)
        resulting_chains = []
        def sorting(s):
            return random.randint(0, 10000000)

        random.seed(10)

        for word in self.to_cfg().get_words(range_2):
            if len(word) < range_1:
                continue
            word = "".join([x.to_text() for x in word])
            resulting_chains.append(word)

        resulting_chains.sort(key=sorting)

        return resulting_chains
