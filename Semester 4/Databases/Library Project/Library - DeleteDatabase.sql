-- Deleting tables in the following order:
-- 12. Languages
-- 11. Genres
-- 10. Authors
--  9. Publishers
--  8. Books
--  7. Branches
--  6. Employees
--  5. BookCopies
--  4. Readers
--  3. ReadersBlacklist
--  2. Rentals
--  1. Returns

USE Library

DROP TABLE [Library].[dbo].[Returns];
GO
DROP TABLE [Library].[dbo].[Rentals];
GO
DROP TABLE [Library].[dbo].[ReadersBlacklist];
GO
DROP TABLE [Library].[dbo].[Readers];
GO
DROP TABLE [Library].[dbo].[BookCopies];
GO
DROP TABLE [Library].[dbo].[Employees];
GO
DROP TABLE [Library].[dbo].[Branches];
GO
DROP TABLE [Library].[dbo].[Books];
GO
DROP TABLE [Library].[dbo].[Publishers];
GO
DROP TABLE [Library].[dbo].[Authors];
GO
DROP TABLE [Library].[dbo].[Genres];
GO
DROP TABLE [Library].[dbo].[Languages];
GO

-- -- DB may be locked by a process. If you have problems 
-- -- deleting the database only with the DROP DATABASE statement, 
-- -- uncomment and execute this code before DROP DATABASE:
-- DECLARE @DatabaseName nvarchar(50)
-- SET @DatabaseName = N'Library'
-- DECLARE @SQL varchar(max)
-- SELECT
--     @SQL = COALESCE(@SQL,'') + 'Kill ' + CONVERT(varchar, SPId) + ';'
-- FROM
--     MASTER..SysProcesses
-- WHERE DBId = DB_ID(@DatabaseName) AND SPId <> @@SPId
-- EXEC(@SQL)

USE master
GO
DROP DATABASE Library;
GO