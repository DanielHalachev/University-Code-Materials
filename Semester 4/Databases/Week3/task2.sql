--1
-- SELECT DISTINCT product.maker
-- FROM product
-- WHERE product.[type]='pc' AND product.model IN (SELECT pc.model FROM pc WHERE pc.speed>500);

--2
-- SELECT printer.code, printer.model, printer.price
-- FROM printer
-- WHERE printer.price = (SELECT MAX(printer.price)FROM printer);

--3
-- SELECT laptop.code, laptop.model, laptop.speed, laptop.ram, laptop.hd, laptop.price, laptop.screen
-- FROM laptop
-- WHERE laptop.speed < ALL(SELECT pc.speed FROM pc);

--4
SELECT pr.model, r.price
FROM product pr, (SELECT pc.model AS model, pc.price AS price FROM pc UNION SELECT laptop.model, laptop.price FROM laptop UNION SELECT printer.model, printer.price FROM printer) r
WHERE pr.model=r.model AND r.price>=ALL(SELECT pc.price AS price FROM pc UNION SELECT laptop.price FROM laptop UNION SELECT printer.price FROM printer);

-- 5
-- SELECT product.maker
-- FROM product
-- WHERE product.type = 'printer' AND product.model IN (SELECT printer.model FROM printer WHERE printer.price=(SELECT MIN(printer.price)FROM printer WHERE printer.color='y')AND printer.color='y')

--6
-- SELECT DISTINCT product.maker
-- FROM product
-- WHERE product.[type]='pc' AND product.model IN 
-- (SELECT pc.model FROM PC WHERE pc.speed=
--     (SELECT MAX(pc.speed)
--     FROM pc
--     WHERE pc.model IN 
--         (SELECT pc.model FROM pc WHERE pc.ram=
--             (SELECT MIN(pc.ram) FROM pc)
--         )
--     )
-- )
