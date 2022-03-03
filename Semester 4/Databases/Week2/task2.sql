-- 1
SELECT p.maker, l.speed
FROM product p, laptop l
WHERE l.hd>9 AND p.type='laptop' AND p.model=l.model

--2
SELECT p.model, l.price
FROM product p, laptop l
WHERE p.maker='B' AND p.type='laptop' AND p.model=l.model
UNION
SELECT p.model, pc1.price
FROM product p, pc pc1
WHERE p.maker='B' AND p.type='pc' AND p.model=pc1.model
UNION
SELECT p.model, pr.price
FROM product p, printer pr
WHERE p.maker='B' AND p.type='printer' AND p.model=pr.model;

--3
SELECT DISTINCT p.maker
FROM product p
WHERE p.type='laptop'
EXCEPT
SELECT DISTINCT p.maker
FROM product p
WHERE p.[type]='pc';

-- 4
SELECT p.hd
FROM pc p
GROUP BY p.hd
HAVING COUNT(p.hd)>1;

--5
SELECT p1.model, p2.model
FROM pc p1, pc p2
WHERE p1.speed=p2.speed AND p1.ram=p2.ram AND p1.model<p2.model;

--6
SELECT p.maker
FROM pc p1, product p
WHERE p1.speed>400 AND p.[type]='pc' AND p.model=p1.model
GROUP BY p.maker
HAVING COUNT(p.model)>2;