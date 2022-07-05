USE master
-- Create the new 'Library' database if it does not exist already
IF NOT EXISTS (
    SELECT
    [name]
FROM
    sys.databases
WHERE [name] = N'Library'
)
CREATE DATABASE Library
    COLLATE Cyrillic_General_CI_AS; -- this setting should enable Cyrillic support if the SQL Server instance enables it
GO

USE Library;
GO

-- Creating tables in the following order:
--  1. Languages
--  2. Genres
--  3. Authors
--  4. Publishers
--  5. Books
--  6. Branches
--  7. Employees
--  8. BookCopies
--  9. Readers
-- 10. ReadersBlacklist
-- 11. Rentals
-- 12. Returns


-- Languages
IF OBJECT_ID('[dbo].[Languages]', 'U') IS NOT NULL
DROP TABLE [dbo].[Languages]
GO
CREATE TABLE [Library].[dbo].[Languages]
(
    [Code] char(2)      NOT NULL,
    [Name] nvarchar(50) NOT NULL,
    CONSTRAINT [PK_Languages] PRIMARY KEY CLUSTERED ([Code] ASC)
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table containing the set of all languages of books in the library. It is used to close the set of all possible Languages, used in the Books table.', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Languages';
GO

-- Genres
IF OBJECT_ID('[dbo].[Genres]', 'U') IS NOT NULL
DROP TABLE [dbo].[Genres]
GO
CREATE TABLE [Library].[dbo].[Genres]
(
    [Name] nvarchar(50) NOT NULL,
    CONSTRAINT [PK_Genres] PRIMARY KEY CLUSTERED ([Name] ASC)
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store all genres of books in the library. It is used to close the set of all Genres of books in the Books table', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Genres';
GO

-- Authors
IF OBJECT_ID('[dbo].[Authors]', 'U') IS NOT NULL
DROP TABLE [dbo].[Authors]
GO
CREATE TABLE [Library].[dbo].[Authors]
(
    [Name]     nvarchar(50)  NOT NULL,
    [RealName] nvarchar(100) NULL,
    [Country]  nvarchar(50)  NULL,
    CONSTRAINT [PK_Authors] PRIMARY KEY CLUSTERED ([Name] ASC)
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store all authors of books in the library. It is used to close the set of all AUthors of books in the Books table', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Authors';
GO

-- Publishers
IF OBJECT_ID('[dbo].[Publishers]', 'U') IS NOT NULL
DROP TABLE [dbo].[Publishers]
GO
CREATE TABLE [Library].[dbo].[Publishers]
(
    [ID]      int          IDENTITY (1, 1) NOT NULL,
    [Name]    nvarchar(50) NOT NULL,
    [City]    nvarchar(50) NULL,
    [Address] nvarchar(50) NULL,
    CONSTRAINT [PK_Publishers] PRIMARY KEY CLUSTERED ([ID] ASC)
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store additional information about book publishers such as their address.', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Publishers';
GO

-- Books
IF OBJECT_ID('[dbo].[Books]', 'U') IS NOT NULL
DROP TABLE [dbo].[Books]
GO
CREATE TABLE [Library].[dbo].[Books]
(
    [ID]            int          IDENTITY (1, 1) NOT NULL,
    [Title]         nvarchar(50) NOT NULL,
    [Author]        nvarchar(50) NOT NULL,
    [PublisherID]   int          NOT NULL,
    [LanguageCode]  char(2)      NOT NULL,
    [Genre]         nvarchar(50) NOT NULL,
    [DatePublished] date         NOT NULL,
    [ISBN]          char(13)     NULL,-- ISBN is used in Bulgaria only after 1991, many books may be older than that, thus have no ISBN
    CONSTRAINT [PK_Books] PRIMARY KEY CLUSTERED ([ID] ASC),
    CONSTRAINT [FK_Books_Author] FOREIGN KEY ([Author])  REFERENCES [Library].[dbo].[Authors]([Name]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [FK_Books_Genres] FOREIGN KEY ([Genre])  REFERENCES [Library].[dbo].[Genres]([Name]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [FK_Books_Languages] FOREIGN KEY ([LanguageCode])  REFERENCES [Library].[dbo].[Languages]([Code]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [FK_Books_Publishers] FOREIGN KEY ([PublisherID])  REFERENCES [Library].[dbo].[Publishers]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION
);
GO
CREATE NONCLUSTERED INDEX [IX_Books_Author] ON [Library].[dbo].[Books] 
 (
  [Author] ASC
 )

GO
CREATE NONCLUSTERED INDEX [IX_Books_Genre] ON [Library].[dbo].[Books] 
 (
  [Genre] ASC
 )

GO
CREATE NONCLUSTERED INDEX [IX_Books_LanguageCode] ON [Library].[dbo].[Books] 
 (
  [LanguageCode] ASC
 )

GO
CREATE NONCLUSTERED INDEX [IX_Books_PublisherID] ON [Library].[dbo].[Books] 
 (
  [PublisherID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store information about a particular book', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Books';
GO

-- Branches
IF OBJECT_ID('[dbo].[Branches]', 'U') IS NOT NULL
DROP TABLE [dbo].[Branches]
GO
CREATE TABLE [Library].[dbo].[Branches]
(
    [ID]      int          IDENTITY (1, 1) NOT NULL,
    [Name]    nvarchar(50) NOT NULL,
    [City]    nvarchar(50) NOT NULL,
    [Address] nvarchar(50) NOT NULL,
    CONSTRAINT [PK_Branches] PRIMARY KEY CLUSTERED ([ID] ASC)
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store all branches of the Library organisation (a library could have multiple offices in different cities or in one city).', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Branches';
GO

-- Employees
IF OBJECT_ID('[dbo].[Employees]', 'U') IS NOT NULL
DROP TABLE [dbo].[Employees]
GO
CREATE TABLE [Library].[dbo].[Employees]
(
    [ID]                int          IDENTITY (1, 1) NOT NULL,
    [BranchID]          int          NOT NULL,
    [FirstName]         nvarchar(50) NOT NULL,
    [LastName]          nvarchar(50) NOT NULL,
    [CitizenshipNumber] nchar(10)    UNIQUE NOT NULL,-- it is extremely unlikely someone would change EGN and add Cyrillic symbols but still...
    [City]              nvarchar(50) NOT NULL,
    [Address]           nvarchar(50) NOT NULL,
    [PhoneNumber]       varchar(15)  NULL,-- not UNIQUE because there may be two people using the same stationary phone
    [Email]             nvarchar(50) UNIQUE NULL,-- it's not such a hardship to create an email for the library
    [IBAN]              varchar(34)  NULL,
    CONSTRAINT [PK_Employees] PRIMARY KEY CLUSTERED ([ID] ASC),
    CONSTRAINT [FK_Employees_Branches] FOREIGN KEY ([BranchID])  REFERENCES [Library].[dbo].[Branches]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [CHK_Employees_Email] CHECK([Email] LIKE '%_@%__.%__')
);
GO
CREATE NONCLUSTERED INDEX [IX_Employees_Branches] ON [Library].[dbo].[Employees] 
 (
  [BranchID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store all employees working for the Library in all branches', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Employees';
GO

-- BookCopies
IF OBJECT_ID('[dbo].[BookCopies]', 'U') IS NOT NULL
DROP TABLE [dbo].[BookCopies]
GO
CREATE TABLE [Library].[dbo].[BookCopies]
(
    [ID]        uniqueidentifier NOT NULL,
    [BookID]    int              NOT NULL,
    [BranchID]  int              NOT NULL,
    [Condition] nvarchar(100)    NULL,
    CONSTRAINT [PK_BookCopies] PRIMARY KEY CLUSTERED ([ID] ASC),
    CONSTRAINT [FK_BookCopies_Books] FOREIGN KEY ([BookID])  REFERENCES [Library].[dbo].[Books]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [FK_BookCopies_Branches] FOREIGN KEY ([BranchID])  REFERENCES [Library].[dbo].[Branches]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION
);
GO
CREATE NONCLUSTERED INDEX [IX_BookCopies_BookID] ON [Library].[dbo].[BookCopies] 
 (
  [BookID] ASC
 )

GO
CREATE NONCLUSTERED INDEX [IX_BookCopies_BranchID] ON [Library].[dbo].[BookCopies] 
 (
  [BranchID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store all physical instances of a books.', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'BookCopies';
GO

-- Readers
IF OBJECT_ID('[dbo].[Readers]', 'U') IS NOT NULL
DROP TABLE [dbo].[Readers]
GO
CREATE TABLE [Library].[dbo].[Readers]
(
    [ID]                int          IDENTITY (1, 1) NOT NULL,
    [FirstName]         nvarchar(50) NOT NULL,
    [LastName]          nvarchar(50) NOT NULL,
    [CitizenshipNumber] nchar(10)    UNIQUE NOT NULL,--analogous to Table Employees
    [City]              nvarchar(50) NOT NULL,
    [Address]           nvarchar(50) NOT NULL,
    [PhoneNumber]       varchar(15)  NULL,
    [Email]             nvarchar(50) UNIQUE NULL,-- it's not such a hardship to create an email for the library
    [Joined]            date         NOT NULL,
    [MembershipEnding]  date         NOT NULL,
    CONSTRAINT [PK_Readers] PRIMARY KEY CLUSTERED ([ID] ASC),
    CONSTRAINT [CHK_Readers_Email] CHECK ([Email] LIKE '%_@__%.__%'),
    CONSTRAINT [CHK_Readers_Dates] CHECK ([Joined]<[MembershipEnding])
);
GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store the people who have registered to use the library', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Readers';
GO

-- ReadersBlacklist
IF OBJECT_ID('[dbo].[ReadersBlacklist]', 'U') IS NOT NULL
DROP TABLE [dbo].[ReadersBlacklist]
GO
CREATE TABLE [Library].[dbo].[ReadersBlacklist]
(
    [ReaderID] int           NOT NULL,
    [From]     date          NULL,
    [To]       date          NULL,-- when the ban expires, the row in the table could serve as history, which could be useful for future reference
    [Reason]   nvarchar(100) NULL,
    CONSTRAINT [PK_ReadersBlacklist] PRIMARY KEY CLUSTERED ([ReaderID] ASC),
    CONSTRAINT [CHK_ReadersBlacklist_Dates] CHECK ([From]<[To]),
    CONSTRAINT [FK_Readers_Blacklist_Readers] FOREIGN KEY ([ReaderID])  REFERENCES [Library].[dbo].[Readers]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION
);
GO
CREATE NONCLUSTERED INDEX [IX_ReadersBlacklist_ReaderID] ON [Library].[dbo].[ReadersBlacklist] 
 (
  [ReaderID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store readers, who are not welcome in any of the library''s branches', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'ReadersBlacklist';
GO

-- Rentals
IF OBJECT_ID('[dbo].[Rentals]', 'U') IS NOT NULL
DROP TABLE [dbo].[Rentals]
GO
CREATE TABLE [Library].[dbo].[Rentals]
(
    [ID]         uniqueidentifier NOT NULL,
    [ReaderID]   int              NOT NULL,
    [BookCopyID] uniqueidentifier NOT NULL,
    [From]       date             NOT NULL,
    [To]         date             NOT NULL,
    [Comment]    nvarchar(100)    NULL,
    CONSTRAINT [PK_Rentals] PRIMARY KEY CLUSTERED ([ID] ASC),
    CONSTRAINT [CHK_Rentals_Dates] CHECK([From]<[To]),
    CONSTRAINT [FK_Rentals_BookCopies] FOREIGN KEY ([BookCopyID])  REFERENCES [Library].[dbo].[BookCopies]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION,
    CONSTRAINT [FK_Rentals_Readers] FOREIGN KEY ([ReaderID])  REFERENCES [Library].[dbo].[Readers]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION
);
GO
CREATE NONCLUSTERED INDEX [IX_Rentals_ReaderID] ON [Library].[dbo].[Rentals] 
 (
  [ReaderID] ASC
 )

GO
CREATE NONCLUSTERED INDEX [IX_Rentals_BookCopyID] ON [Library].[dbo].[Rentals] 
 (
  [BookCopyID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store books, which are currently borrowed by readers of the library', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Rentals';
GO

-- Returns
IF OBJECT_ID('[dbo].[Returns]', 'U') IS NOT NULL
DROP TABLE [dbo].[Returns]
GO
CREATE TABLE [Library].[dbo].[Returns]
(
    [RentalID]   uniqueidentifier NOT NULL,
    [ReturnDate] datetime         NOT NULL,
    [Damage]     nvarchar(100)    NULL,
    CONSTRAINT [PK_Returns] PRIMARY KEY CLUSTERED ([RentalID] ASC),
    CONSTRAINT [FK_Returns_Rentals] FOREIGN KEY ([RentalID])  REFERENCES [Library].[dbo].[Rentals]([ID]) ON UPDATE CASCADE ON DELETE NO ACTION
);
GO
CREATE NONCLUSTERED INDEX [IX_Returns_RentalID] ON [Library].[dbo].[Returns] 
 (
  [RentalID] ASC
 )

GO
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'A table to store the return information after every rental', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'Returns';
GO