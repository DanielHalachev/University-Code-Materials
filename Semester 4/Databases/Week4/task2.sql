--1
SELECT product.maker, product.model, product.[type]
FROM product
WHERE product.model NOT IN (SELECT pc.model FROM pc) AND product.model NOT IN (SELECT laptop.model FROM laptop) AND product.model NOT IN (SELECT printer.model FROM printer);

--2
SELECT product.maker
FROM product JOIN laptop ON product.model=laptop.model
INTERSECT
SELECT product.maker
FROM product JOIN printer ON product.model=printer.model

--3 ???
-- SELECT laptop.hd
-- FROM laptop WHERE 

-- 4
SELECT p.model
FROM pc p WHERE p.model IN (SELECT product.model FROM product WHERE product.maker IS NULL); 