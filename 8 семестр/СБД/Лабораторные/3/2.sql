CREATE OR REPLACE FUNCTION format_amount(amount IN NUMBER)
RETURN VARCHAR2
IS
    rubles VARCHAR2(100);
    kopecks VARCHAR2(100);
    result VARCHAR2(200);
BEGIN
    -- Вычисляем количество рублей и копеек
    rubles := TO_CHAR(TRUNC(amount), '999999999');
    kopecks := TO_CHAR(MOD(amount, 1) * 100, '09');

    -- Склонение слов "рубль" и "копейка" по правилам русского языка
    IF rubles = '1' THEN
        rubles := rubles || ' рубль';
    ELSIF rubles IN ('2', '3', '4') THEN
        rubles := rubles || ' рубля';
    ELSE
        rubles := rubles || ' рублей';
    END IF;

    IF kopecks = '01' THEN
        kopecks := kopecks || ' копейка';
    ELSIF kopecks IN ('02', '03', '04') THEN
        kopecks := kopecks || ' копейки';
    ELSE
        kopecks := kopecks || ' копеек';
    END IF;

    -- Составляем строку результата
    result := rubles || ' ' || kopecks;

    RETURN result;
END;
/
SELECT onum, format_amount(AMT) FROM ord;
