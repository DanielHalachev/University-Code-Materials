--1
SELECT DISTINCT SHIPS.NAME
FROM SHIPS
WHERE (SHIPS.NAME LIKE 'C%' or SHIPS.NAME LIKE 'K%') AND SHIPS.NAME IN (SELECT OUTCOMES.SHIP FROM OUTCOMES);

--2
SELECT SHIPS.NAME, CLASSES.COUNTRY
FROM SHIPS, CLASSES
WHERE SHIPS.CLASS=CLASSES.CLASS AND SHIPS.NAME NOT IN (SELECT OUTCOMES.SHIP FROM OUTCOMES WHERE OUTCOMES.RESULT='sunk');

--3
SELECT CLASSES.COUNTRY, COUNT(OUTCOMES.SHIP) AS COUNT_OF_SUNK_SHIPS
FROM CLASSES 
LEFT JOIN SHIPS ON CLASSES.CLASS=SHIPS.CLASS -- to include countries with no ships
LEFT JOIN OUTCOMES ON OUTCOMES.SHIP=SHIPS.NAME and OUTCOMES.RESULT='sunk'
GROUP BY CLASSES.COUNTRY;

--4
SELECT OUTCOMES.BATTLE
FROM OUTCOMES
GROUP BY OUTCOMES.BATTLE
HAVING COUNT(OUTCOMES.SHIP) > (SELECT COUNT(OUTCOMES.SHIP) FROM OUTCOMES WHERE OUTCOMES.BATTLE='Guadalcanal');

--5
SELECT OUTCOMES.BATTLE
FROM OUTCOMES
GROUP BY OUTCOMES.BATTLE
HAVING COUNT(OUTCOMES.SHIP) > (SELECT COUNT(OUTCOMES.SHIP) FROM OUTCOMES WHERE OUTCOMES.BATTLE='Surigao Strait');



--6
SELECT s.NAME, c.DISPLACEMENT, c.NUMGUNS
FROM SHIPS s, CLASSES c
WHERE s.CLASS=c.CLASS 
AND c.DISPLACEMENT=(SELECT MIN(c1.DISPLACEMENT) FROM CLASSES c1)
AND c.NUMGUNS >= (SELECT MAX(c2.NUMGUNS) FROM CLASSES c2 WHERE c2.DISPLACEMENT=c.DISPLACEMENT)
ORDER BY c.NUMGUNS;

--7
SELECT COUNT(DISTINCT o1.SHIP)
FROM OUTCOMES o1, OUTCOMES o2, BATTLES b1, BATTLES b2
WHERE o1.RESULT='damaged' and o2.RESULT='ok'    -- damaged in the first battle and won in the second
AND o1.SHIP=o2.SHIP                             -- the same ship
AND o1.BATTLE=b1.[NAME] AND o2.BATTLE=b2.NAME   -- get the battles to compare them by date
AND b1.[DATE]<b2.[DATE];
