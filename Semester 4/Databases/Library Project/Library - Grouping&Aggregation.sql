USE Library

-- 1. Градове на читатели и брой читатели на библиотеката от тях
SELECT
    Readers.City AS Град,
    COUNT(*) AS [Брой читатели]
FROM
    dbo.Readers
GROUP BY City;

-- 2. Първи читател в черния списък (по хронология)
SELECT
    Readers.FirstName AS Име,
    Readers.LastName AS Фамилия,
    MIN(ReadersBlacklist.[From]) AS [Дата]
FROM
    dbo.Readers JOIN dbo.ReadersBlacklist ON Readers.ID=ReadersBlacklist.ReaderID
GROUP BY Readers.FirstName, Readers.LastName;

-- 3. Първият читател в библиотеката
SELECT
    Readers.FirstName AS [Име],
    Readers.LastName AS [Фамилия],
    Readers.Joined AS [Член от]
FROM
    Readers
GROUP BY Readers.FirstName, Readers.LastName, Readers.Joined
HAVING (Readers.Joined=(SELECT
    MIN(Readers.Joined)
FROM
    Readers))

-- 4.1 Всички книги на Агата Кристи по брой във всеки филиал
SELECT
    Books.Title AS [Заглавие],
    Books.DatePublished [Дата на публикуване],
    Books.PublisherID AS [Номер на издател],
    Books.ISBN,
    ISNULL(r1.Branch1, 0) AS [Филиал 1],
    ISNULL(r1.Branch2, 0) AS [Филиал 2],
    ISNULL(r1.Branch3, 0) AS [Филиал 3]
FROM
    Books
    JOIN
    (SELECT
        copies.BookID,
        br1.Branch1,
        br2.Branch2,
        br3.Branch3
    FROM
        BookCopies copies
        JOIN
        (SELECT
            BookCopies.BookID,
            COUNT(BookCopies.BranchID) AS Branch1
        FROM
            BookCopies
        GROUP BY BookCopies.BookID, BookCopies.BranchID
        HAVING BookCopies.BranchID=1) br1
        ON copies.BookID=br1.BookID
        FULL JOIN
        (SELECT
            BookCopies.BookID,
            COUNT(BookCopies.BranchID) AS Branch2
        FROM
            BookCopies
        GROUP BY BookCopies.BookID, BookCopies.BranchID
        HAVING BookCopies.BranchID=2) br2
        ON copies.BookID=br2.BookID
        FULL JOIN
        (SELECT
            BookCopies.BookID,
            COUNT(BookCopies.BranchID) AS Branch3
        FROM
            BookCopies
        GROUP BY BookCopies.BookID, BookCopies.BranchID
        HAVING BookCopies.BranchID=3) br3
        ON copies.BookID=br3.BookID
    GROUP BY copies.BookID, br1.Branch1, br2.Branch2, br3.Branch3) r1
    ON Books.ID=r1.BookID
WHERE Books.Author='Агата Кристи'

-- 4.2 Всички книги на Агата Кристи по брой във всеки филиал
-- тази версия ускорява заявката и решава проблема с промяна в броя на филиалите
-- но съдържа неизучаван материал
DECLARE @branches AS nvarchar(MAX);
SET @branches='';
SELECT
    @branches+= STRING_AGG(CONCAT('[',Branches.ID,']'),',')
FROM
    Branches;
DECLARE @cols AS nvarchar(MAX);
SET @cols='';
SELECT
    @cols+= STRING_AGG(CONCAT('ISNULL([',Branches.ID,'],0) AS [Филиал ',Branches.ID,']'),', ')
FROM
    Branches;
DECLARE @q AS nvarchar(MAX);
SET @q='
SELECT Books.Title AS [Заглавие], Books.DatePublished AS [Дата на публикуване], Books.PublisherID AS [Номер на издател], Books.ISBN, '+@cols+'
FROM Books JOIN 
(SELECT * FROM
    (SELECT
        BookCopies.BookID,
        BookCopies.BranchID,
        COUNT(*) AS [Count]
    FROM
        BookCopies
    GROUP BY BookCopies.BookID, BookCopies.BranchID
    ) SourceTable
PIVOT (
    SUM([Count])
    FOR [BranchID]
    IN ('+@branches+')
) AS PivotTable) t ON Books.ID=t.BookID
WHERE Books.Author = ''Агата Кристи''';
EXEC(@q)

-- 5. Брой книги във всеки град, където има филиал
SELECT
    Branches.City AS Град,
    counts.counts AS [Брой физически книги]
FROM
    Branches
    JOIN
    (SELECT
        BookCopies.BranchID,
        COUNT(BookCopies.BookID) AS counts
    FROM
        BookCopies
    GROUP BY BookCopies.BranchID) counts
    ON Branches.ID=counts.BranchID;

-- 6. Автори и брой наети книги от тях в намаляващ ред
SELECT
    Books.Author AS [Автор],
    COUNT(*) AS [Брой наети книги]
FROM
    Rentals JOIN BookCopies ON Rentals.BookCopyID=BookCopies.ID JOIN Books ON BookCopies.BookID=Books.ID
GROUP BY Books.Author
ORDER BY [Брой наети книги] DESC;

-- 7. Читателите в библиотеката, предали книгите си с най-голямо закъснение
SELECT
    Readers.FirstName AS Име,
    Readers.LastName AS Фамилия,
    Readers.CitizenshipNumber AS ЕГН,
    Readers.City AS Град,
    diff.MaxDiff AS Закъснение
FROM
    Readers JOIN
    (SELECT
        Rentals.ReaderID,
        MAX(DATEDIFF(day,Rentals.[To], [Returns].[ReturnDate])) AS MaxDiff
    FROM
        Rentals RIGHT JOIN [Returns] ON Rentals.ID=[Returns].RentalID
    GROUP BY Rentals.ReaderID
    HAVING (MAX(DATEDIFF(day,Rentals.[To], [Returns].[ReturnDate]))=(SELECT
        MAX(DATEDIFF(day,Rentals.[To], [Returns].[ReturnDate]))
    FROM
        Rentals RIGHT JOIN [Returns] ON Rentals.ID=[Returns].RentalID)))
diff
    ON Readers.ID=diff.ReaderID;

-- 8.  Езиците, на които са написани книгите в библиотеката и колко физически екземпляра има от тях
SELECT
    Languages.Name AS [Език],
    Languages.Code AS [Код],
    COUNT(Languages.Code) AS [Брой екземпляри на този език]
FROM
    BookCopies JOIN Books ON BookCopies.BookID=Books.ID JOIN Languages ON Books.LanguageCode=Languages.Code
GROUP BY Languages.Name, Languages.Code;

--9. Читателите с най-много взимания в библиотеката
SELECT
    Readers.FirstName AS [Име],
    Readers.LastName AS [Фамилия],
    Readers.CitizenshipNumber AS [ЕГН],
    Readers.City AS [Град],
    COUNT(BookCopyID) AS [Брой взимания]
FROM
    Readers JOIN Rentals ON Readers.ID=Rentals.ReaderID
GROUP BY Readers.FirstName, Readers.LastName, Readers.CitizenshipNumber, Readers.City
HAVING (COUNT(BookCopyID)=(SELECT
    MAX(r.[Count])
FROM(SELECT
        COUNT(BookCopyID) AS Count
    FROM
        Rentals
    GROUP BY ReaderID) r
    )
)

-- 10. Брой закъснели връщания във всеки филиал
SELECT
    Branches.ID,
    Branches.Name AS [Име],
    Branches.City AS [Град],
    COUNT(*) AS [Брой закъснели връщания]
FROM
    Branches JOIN BookCopies ON Branches.ID=BookCopies.BranchID JOIN Rentals ON BookCopies.ID=Rentals.BookCopyID JOIN [Returns] ON Rentals.ID=[Returns].RentalID
WHERE [Rentals].[To]<[Returns].ReturnDate OR [Returns].ReturnDate IS NULL
GROUP BY Branches.ID, Branches.Name, Branches.City;