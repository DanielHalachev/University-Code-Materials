USE Library
GO

INSERT INTO [Library].[dbo].[Languages]
    ([Code],[Name])
VALUES
    ('BG', N'Български'),
    ('EN', N'Английски')
GO

INSERT INTO [Library].[dbo].[Genres]
    ([Name])
VALUES
    (N'Роман'),
    (N'Повест'),
    (N'Стихосбирка'),
    (N'Комедия'),
    (N'Сборник'),
    (N'Криминален роман'),
    (N'Исторически роман')
GO

INSERT INTO [Library].[dbo].[Authors]
    ([Name], [RealName], [Country])
VALUES
    (N'Иван Вазов', N'Иван Вазов', N'България'),
    (N'Елин Пелин', N'Димитър Стоянов', N'България'),
    (N'Александър Дюма - Баща', N'Алексадър Дюма', N'Франция'),
    (N'Етел Лилиан Войнич', N'Етел Лилиан Войнич', N'Великобритания'),
    (N'Ерих Мария Ремарк', N'Ерих Мария Ремарк', N'Германия'),
    (N'Хенрик Сенкевич', N'Хѐнрик А̀дам Алекса̀ндер Пюс Сенкевич', N'Полша'),
    (N'Агата Кристи', N'Дейм Агата Мери Клариса Кристи', N'Великобритания'),
    (N'Карл Май', N'Карл Фридрих Май', N'САЩ'),
    (N'Никола Вапцаров', N'Никола Йонков Вапцаров', N'България'),
    (N'Христо Смирненски', N'Христо Димитров Измирлиев', N'България'),
    (N'Оноре дьо Балзак', N'Оноре Балзак', N'Франция'),
    (N'Мигел де Сервантес', N'Мигел де Сервантес', N'Испания')

GO

INSERT INTO [Library].[dbo].[Publishers]
    ([Name],[City],[Address])
VALUES
    (N'Труд', N'София', N'ул. Драган Цанков 21'),
    (N'Фют', N'София', N'бул. Искърско шосе 7'),
    (N'Сиела', N'София', N'бул. Владимир Вазов 9'),
    (N'Колибри', N'София', 'ул. Иван Вазов 36')
GO

INSERT INTO [Library].[dbo].[Books]
    ([Title],[Author],[PublisherID], [LanguageCode], [Genre], [DatePublished], [ISBN])
VALUES
    ('Смърт край Нил', 'Агата Кристи', '2', 'BG', 'Криминален роман', '1937-11-01', '4215574186436'),
    ('Десет малки негърчета', 'Агата Кристи', '2', 'BG', 'Криминален роман', '1939-11-06', '2472668465523'),
    ('Аферата в Стайлс', 'Агата Кристи', '1', 'EN', 'Криминален роман', '1920-10-01', '2799528122575'),
    ('Quo vadis', 'Хенрик Сенкевич', '3', 'BG', 'Исторически роман', '1894-02-05', '8183136569668'),
    ('Под игото', 'Иван Вазов', '2', 'BG', 'Исторически роман', '1894-07-20', NULL),
    ('Чичовци', 'Иван Вазов', '2', 'BG', 'Исторически роман', '1885-06-11', '2130632056927'),
    ('Гераците', 'Елин Пелин', '2', 'BG', 'Повест', '1911-12-02', '6546476252372'),
    ('Под манастирската лоза', 'Елин Пелин', '2', 'BG', 'Сборник', '1936-03-20', '4775565647882'),
    ('Граф Монте Кристо', 'Александър Дюма - Баща', '1', 'BG', 'Роман', '1844-10-01', '8867858874882'),
    ('Тримата мускетари', 'Александър Дюма - Баща', '1', 'BG', 'Роман', '1844-07-01', '8291551236258'),
    ('Тримата мускетари - 20 години по-късно', 'Александър Дюма - Баща', '1', 'BG', 'Роман', '1845-06-17', '4815568451697'),
    ('Тримата мускетари - още 10 години по-късно', 'Александър Дюма - Баща', '1', 'BG', 'Роман', '1847-09-01', '5770166133736'),
    ('Стършел', 'Етел Лилиан Войнич', '3', 'BG', 'Роман', '1897-06-01', '2178101065132'),
    ('Време да се живее и време да се мре', 'Ерих Мария Ремарк', '3', 'BG', 'Роман', '1954-07-01', '4484847124273'),
    ('Сенки в рая', 'Ерих Мария Ремарк', '3', 'BG', 'Роман', '1971-11-10', '9234677187444'),
    ('На Западния фронт нищо ново', 'Ерих Мария Ремарк', '3', 'BG', 'Роман', '1928-12-09', '0457877347273'),
    ('Съкровището в Сребърното езеро', 'Карл Май', '4', 'BG', 'Роман', '1891-01-01', '2978128836871'),
    ('Моторни песни', 'Никола Вапцаров', '2', 'BG', 'Сборник', '1940-06-05', '8891812759744'),
    ('Да бъде ден!', 'Христо Смирненски', '2', 'BG', 'Сборник', '1922-03-05', '2433561553784'),
    ('Знаменитият идалго Дон Кихот де ла Манча', 'Мигел де Сервантес', '4', 'BG', 'Роман', '1605-01-01', '9353675483605'),
    ('Дядо Горио', 'Оноре дьо Балзак', '1', 'BG', 'Роман', '1835-05-12', '5662813484531')
GO

INSERT INTO [Library].[dbo].[Branches]
    ([Name], [City], [Address])
VALUES
    (N'Централна библиотека', N'София', N'бул. Черни връх 20'),
    (N'Градска библиотека', N'Пловдив', N'ул. Стефан Стамболов 4'),
    (N'Библиотека Христо Смирненски', N'Варна', N'ул. Дръзки 12')
GO


INSERT INTO [Library].[dbo].[BookCopies]
    ([ID], [BookID],[BranchID],[Condition])
VALUES
    (NEWID(), 1, 1, 'Отлично'),
    (NEWID(), 1, 1, 'Отлично'),
    (NEWID(), 1, 1, 'Добро'),
    (NEWID(), 2, 1, 'Отлично'),
    (NEWID(), 2, 1, 'Добро'),
    (NEWID(), 3, 1, 'Добро'),
    (NEWID(), 3, 1, 'Лошо'),
    (NEWID(), 4, 1, 'Отлично'),
    (NEWID(), 5, 1, 'Отлично'),
    (NEWID(), 5, 1, 'Отлично'),
    (NEWID(), 5, 1, 'Добро'),
    (NEWID(), 6, 1, 'Отлично'),
    (NEWID(), 6, 1, 'Добро'),
    (NEWID(), 7, 1, 'Лошо'),
    (NEWID(), 7, 1, 'Добро'),
    (NEWID(), 8, 1, 'Отлично'),
    (NEWID(), 9, 1, 'Отлично'),
    (NEWID(), 9, 1, 'Отлично'),
    (NEWID(), 9, 1, 'Добро'),
    (NEWID(), 10, 1, 'Много лошо'),
    (NEWID(), 11, 1, 'Много добро'),
    (NEWID(), 12, 1, 'Отлично'),
    (NEWID(), 13, 1, 'Отлично'),
    (NEWID(), 14, 1, 'Много добро'),
    (NEWID(), 15, 1, 'Отлично'),
    (NEWID(), 16, 1, 'Лошо'),
    (NEWID(), 16, 1, 'Отлично'),
    (NEWID(), 16, 1, 'Добро'),
    (NEWID(), 17, 1, 'Отлично'),
    (NEWID(), 17, 1, 'Отлично'),
    (NEWID(), 18, 1, 'Отлично'),
    (NEWID(), 18, 1, 'Добро'),
    (NEWID(), 18, 1, 'Добро'),
    (NEWID(), 19, 1, 'Отлично'),
    (NEWID(), 19, 1, 'Много добро'),
    (NEWID(), 20, 1, 'Добро'),
    (NEWID(), 20, 1, 'Добро'),
    (NEWID(), 20, 1, 'Отлично')
GO

INSERT INTO [Library].[dbo].[BookCopies]
    ([ID], [BookID],[BranchID],[Condition])
VALUES
    (NEWID(), 1, 2, 'Лошо'),
    (NEWID(), 1, 2, 'Отлично'),
    (NEWID(), 1, 2, 'Добро'),
    (NEWID(), 2, 2, 'Отлично'),
    (NEWID(), 2, 2, 'Добро'),
    (NEWID(), 3, 2, 'Лошо'),
    (NEWID(), 4, 2, 'Отлично'),
    (NEWID(), 5, 2, 'Много добро'),
    (NEWID(), 5, 2, 'Отлично'),
    (NEWID(), 5, 2, 'Добро'),
    (NEWID(), 6, 2, 'Отлично'),
    (NEWID(), 6, 2, 'Добро'),
    (NEWID(), 7, 2, 'Лошо'),
    (NEWID(), 7, 2, 'Добро'),
    (NEWID(), 8, 2, 'Отлично'),
    (NEWID(), 9, 2, 'Отлично'),
    (NEWID(), 9, 2, 'Добро'),
    (NEWID(), 10, 2, 'Много лошо'),
    (NEWID(), 11, 2, 'Много добро'),
    (NEWID(), 12, 2, 'Отлично'),
    (NEWID(), 13, 2, 'Отлично'),
    (NEWID(), 14, 2, 'Много добро'),
    (NEWID(), 15, 2, 'Отлично'),
    (NEWID(), 16, 2, 'Лошо'),
    (NEWID(), 16, 2, 'Отлично'),
    (NEWID(), 16, 2, 'Добро'),
    (NEWID(), 17, 2, 'Отлично'),
    (NEWID(), 17, 2, 'Много добро'),
    (NEWID(), 18, 2, 'Отлично'),
    (NEWID(), 18, 2, 'Добро'),
    (NEWID(), 19, 2, 'Отлично'),
    (NEWID(), 19, 2, 'Много добро'),
    (NEWID(), 20, 2, 'Добро'),
    (NEWID(), 20, 2, 'Лошо'),
    (NEWID(), 20, 2, 'Отлично')
GO

INSERT INTO [Library].[dbo].[BookCopies]
    ([ID],[BookID],[BranchID],[Condition])
VALUES
    (NEWID(), 1, 3, 'Много добро'),
    (NEWID(), 1, 3, 'Отлично'),
    (NEWID(), 1, 3, 'Добро'),
    (NEWID(), 2, 3, 'Отлично'),
    (NEWID(), 2, 3, 'Добро'),
    (NEWID(), 3, 3, 'Добро'),
    (NEWID(), 3, 3, 'Лошо'),
    (NEWID(), 4, 3, 'Много лошо'),
    (NEWID(), 5, 3, 'Добро'),
    (NEWID(), 5, 3, 'Отлично'),
    (NEWID(), 5, 3, 'Добро'),
    (NEWID(), 6, 3, 'Отлично'),
    (NEWID(), 6, 3, 'Добро'),
    (NEWID(), 7, 3, 'Лошо'),
    (NEWID(), 7, 3, 'Добро'),
    (NEWID(), 8, 3, 'Отлично'),
    (NEWID(), 9, 3, 'Много добро'),
    (NEWID(), 9, 3, 'Отлично'),
    (NEWID(), 9, 3, 'Добро'),
    (NEWID(), 10, 3, 'Много лошо'),
    (NEWID(), 11, 3, 'Много добро'),
    (NEWID(), 12, 3, 'Отлично'),
    (NEWID(), 13, 3, 'Отлично'),
    (NEWID(), 14, 3, 'Много добро'),
    (NEWID(), 15, 3, 'Отлично'),
    (NEWID(), 16, 3, 'Лошо'),
    (NEWID(), 16, 3, 'Добро'),
    (NEWID(), 17, 3, 'Отлично'),
    (NEWID(), 17, 3, 'Лошо'),
    (NEWID(), 18, 3, 'Отлично'),
    (NEWID(), 18, 3, 'Добро'),
    (NEWID(), 18, 3, 'Добро'),
    (NEWID(), 19, 3, 'Отлично'),
    (NEWID(), 19, 3, 'Много добро'),
    (NEWID(), 20, 3, 'Добро'),
    (NEWID(), 20, 3, 'Отлично')
GO

INSERT INTO [Library].[dbo].[Employees]
    ([BranchID], [FirstName], [LastName], [CitizenshipNumber], [City], [Address], [PhoneNumber], [Email], [IBAN])
VALUES
    (1, N'Ивайло', N'Ченчев', N'2853034727', N'София', N'улица Яне Сандански 27', '+359 917332966', 'ivaylochenchev@outlook.com', 'GE36991073110379973256'),
    (2, N'Катрин', N'Стоименова', N'0782181761', N'Пловдив', N'улица Осми март 11', '+359 123716527', 'catherinestoimenova@outlook.org', 'BA476961777515611457'),
    (1, N'Ангел', N'Ангелов', N'7634816386', N'София', N'булевард Цариградско шосе 8', '+359 522627184', 'angelofangels@yahoo.org', 'MT74SBIT45868064567682897842181'),
    (1, N'Ирина', N'Куртева', N'3261651768', N'София', N'улица Свищов 14', '+359 267327343', 'irinakurteva@abv.com', 'GT70725327654371566930384044'),
    (2, N'Милена', N'Джамбазова', N'0789114327', N'Пловдив', N'улица Отец Паисий 4', '+359 852349351', 'milenadzhambazova@protonmail.bg', 'CZ0971461626753336536394'),
    (2, N'Емилиян', N'Христов', N'0667164419', N'Пловдив', N'улица Неофит Рилски 20', '+359 667184456', 'emilianhristov@google.co', 'AL30601248104873290147626899'),
    (1, N'Ралица', N'Славчева', N'9162416035', N'София', N'улица Петдесет и четвърти Мински полк', '+359 467885375', 'ralitsaslavcheva@outlook.bg', 'PS781478296605852144618746934'),
    (1, N'Ангел', N'Петров', N'1315181247', N'София', N'улица Георги С.Раковски 21', '+359 577030816', 'angelpetrov@google.co', 'TN4814313540865557976344'),
    (2, N'Павел', N'Христов', N'5353397585', N'Пловдив', N'улица Втора 32', '+359 542262231', 'pavelhristov@protonmail.com', 'BG50WZVR42818076279781'),
    (3, N'Тони', N'Дерлипански', N'0374418520', N'Варна', N'улица Родолюбие 17', '+359 154604838', 'tonyderlipanski@yahoo.com', 'DE73743576405443923466'),
    (2, N'Борислав', N'Ботев', N'7916352443', N'Пловдив', N'улица Любомир Миланов 14', '+359 528799410', 'borislavbotev@abv.co', 'GI23RQMM166048787515181'),
    (2, N'Росен', N'Витлянов', N'8604797558', N'Пловдив', N'улица Димчо Дебелянов 24', '+359 892524232', 'rosenvitlyanov@protonmail.co', 'PL15456769370240930831157623'),
    (1, N'Симеон', N'Николов', N'1155167573', N'София', N'улица Метрополит Герасим 10', '+359 534243015', 'simeonnikolov@protonmail.com', 'AE579871845455109336337'),
    (2, N'Александра', N'Пенева', N'1247123895', N'Пловдив', N'улица Ана Маймункова 18', '+359 685259116', 'alexandrapeneva@icloud.com', 'GE32493578923202714437'),
    (1, N'Илиян', N'Руйков', N'3865341737', N'София', N'улица Сава Доброплодни 2', '+359 856034122', 'ilianruikov@outlook.com', 'GI30VIYD361804392876983'),
    (3, N'Нели', N'Беремска', N'5203871679', N'Варна', N'улица Омуртаг 29', '+359 397816770', 'nellyberemska@yahoo.co', 'GR3801486917693673372489643'),
    (2, N'Крум', N'Стоянов', N'6522839198', N'Пловдив', N'улица Стефан Стамболов 6', '+359 044388525', 'krumstoyanov@icloud.org', 'EE776772521074857944'),
    (2, N'Юлиан', N'Стоев', N'3166181788', N'Пловдив', N'улица Пролетарии 33', '+359 477239250', 'julianstoev@yahoo.org', 'LU280095712283127546'),
    (1, N'Мария', N'Дачева', N'5863527832', N'София', N'улица Мадара 18', '+359 738165586', 'mariadacheva@abv.org', 'GE52929452512808352855'),
    (1, N'Денис', N'Нгуен', N'7115256365', N'София', N'улица Дельо Георгиев 4', '+359 236579788', 'denisnguyen@protonmail.org', 'DK8675308196484923')
GO

INSERT INTO [Library].[dbo].[Readers]
    ([FirstName], [LastName], [CitizenshipNumber], [City], [Address], [PhoneNumber], [Email], [Joined], [MembershipEnding])
VALUES
    (N'Ивайло', N'Ченчев', N'2853034727', N'София', N'улица Яне Сандански 27', '+359 917332966', 'ivaylochenchev@outlook.com', '2018-02-05', '2019-02-05'),
    (N'Катрин', N'Стоименова', N'0782181761', N'Пловдив', N'улица Осми март 11', '+359 123716527', 'catherinestoimenova@outlook.org', '2020-03-05', '2021-03-5'),
    (N'Ангел', N'Ангелов', N'7634816386', N'София', N'булевард Цариградско шосе 8', '+359 522627184', 'angelofangels@yahoo.org', '2018-02-10', '2018-08-10'),
    (N'Ирина', N'Куртева', N'3261651768', N'София', N'улица Свищов 14', '+359 267327343', 'irinakurteva@abv.com', '2018-05-03', '2018-11-03'),
    (N'Милена', N'Джамбазова', N'0789114327', N'Пловдив', N'улица Отец Паисий 4', '+359 852349351', 'milenadzhambazova@protonmail.bg', '2018-03-02', '2018-06-02'),
    (N'Атанас', N'Димитров', '5458453715', N'Пловдив', N'улица Акациите 2', '+359 963193414', 'atanasdimitrov@yahoo.org', '2018-04-26', '2019-04-26'),
    (N'Кристина', N'Кюркчиева', '4583137294', N'София', N'булевард Сливница 19', '+359 776550777', 'kristinakyurkchieva@abv.com', '2021-04-05', '2022-04-05'),
    (N'Кристиян', N'Карлов', '5905254517', N'София', N'улица Боев рид 34', '+359 178714192', 'christiankarlov@outlook.org', '2021-09-03', '2022-09-03'),
    (N'Тома', N'Томов', '6679742461', N'Варна', N'улица Алея Детелина 15', '+359 408444200', 'tomatomov@outlook.bg', '2019-05-25', '2020-05-25'),
    (N'Андрей', N'Георгиев', '2817659773', N'Пловдив', N'улица Княгиня Клементина 23', '+359 473520231', 'andreygeorgiev@yahoo.co', '2022-02-02', '2023-02-02'),
    (N'Стефани', N'Стефанова', '8511591424', N'Пловдив', N'улица Хан Богров 34', '+359 524257422', 'stefanistefanova@protonmail.com', '2019-01-09', '2020-01-09'),
    (N'Венцислав', N'Дженев', '7298824210', N'Пловдив', N'улица Мадара 24', '+359 316808152', 'ventsislavdzhenev@google.com', '2018-07-02', '2019-07-02'),
    (N'Деян', N'Цветков', '5360170008', N'Пловдив', N'улица Шести септември 20', '+359 343887841', 'dejantsvetkov@icloud.com', '2020-11-11', '2021-11-11'),
    (N'Димитър', N'Димитров', '7447125778', N'Варна', N'булевард Съборни 27', '+359 416365447', 'dimitardimitrov@icloud.org', '2020-02-26', '2021-02-26'),
    (N'Мартин', N'Николаев', '5554376876', N'Варна', N'улица Шумни дол 23', '+359 635165449', 'martinnikolaev@google.co', '2019-09-21', '2020-09-21'),
    (N'Жана', N'Оракова', '2752864318', N'Пловдив', N'улица Яне Сандански 2', '+359 680616446', 'zhanaorakova@abv.com', '2020-10-24', '2021-10-24'),
    (N'Владислав', N'Георгиев', '1846622731', N'Пловдив', N'улица Михал Кефалов 17', '+359 687603474', 'vladislavgeorgiev@google.bg', '2021-12-29', '2022-12-29'),
    (N'Виктор', N'Василев', '8011928948', N'Варна', N'улица Плиска 14', '+359 445352966', 'victorvasilev@icloud.org', '2022-01-04', '2023-01-04'),
    (N'Християна', N'Данаилова', '2081715177', N'София', N'улица Софроний 29', '+359 414362515', 'hristianadanailova@abv.co', '2018-08-20', '2019-08-20'),
    (N'Драгомир', N'Тодоров', '1567386713', N'Пловдив', N'улица Стефан Караджа 30', '+359 248450534', 'dragomirtodorov@icloud.bg', '2022-02-08', '2023-02-08'),
    (N'Петър', N'Стоянов', '9747729138', N'Пловдив', N'улица Мир 26', '+359 661920505', 'petarstoyanov@outlook.com', '2020-05-28', '2021-05-28'),
    (N'Петър', N'Милев', '5691436952', N'Варна', N'улица Иван Вазов 27', '+359 657484875', 'petarmilev@yahoo.org', '2021-02-28', '2022-02-28'),
    (N'Иван', N'Борисов', '7168064832', N'Пловдив', N'площад Георги Дражев 34', '+359 823329726', 'ivanborisov@abv.co', '2020-07-23', '2021-07-23'),
    (N'Радостина', N'Хаджиева', '1836488947', N'Пловдив', N'улица Болярска 12', '+359 124170316', 'radostinahadjieva@abv.org', '2020-01-29', '2021-01-29'),
    (N'Димитър', N'Стефанов', '0149224200', N'София', N'улица Георги Бенковски 3', '+359 507473867', 'dimitarstefanov@abv.org', '2021-03-24', '2022-03-24'),
    (N'Карина', N'Георгиева', '8084627985', N'Пловдив', N'улица Шаркьой 35', '+359 486117576', 'karinageorgieva@icloud.bg', '2018-11-26', '2019-11-26'),
    (N'Йосиф', N'Иванов', '1642262491', N'Пловдив', N'Улица Владо Васев 26', '+359 064019127', 'josephivanov@icloud.bg', '2022-01-27', '2023-01-27'),
    (N'Борислав', N'Човански', '6591193658', N'Пловдив', N'улица Филип Миланов Гънев 16', '+359 265546239', 'borislavchovanski@yahoo.co', '2021-07-17', '2022-07-17'),
    (N'Георги', N'Куклев', '2514593633', N'Пловдив', N'улица Еленин връх 9', '+359 504154318', 'georgikuklev@outlook.com', '2020-01-04', '2021-01-04'),
    (N'Йоана', N'Балчева', '8509021272', N'София', N'улица Христо Ботев 5', '+359 425413674', 'joanabalcheva@outlook.org', '2019-08-11', '2020-08-11'),
    (N'Йордан', N'Цолов', '5679323339', N'София', N'улица Стара планина 8', '+359 091281164', 'jordantsolov@outlook.co', '2019-10-12', '2020-10-12'),
    (N'Георги', N'Джамбазов', '3370522223', N'Пловдив', N'улица Младост 31', '+359 648811176', 'georgidzhambazov@icloud.com', '2019-07-08', '2020-07-08'),
    (N'Петър', N'Русев', '5697148366', N'Пловдив', N'улица Александър Стамболийски 12', '+359 817894187', 'peterrusev@icloud.com', '2021-09-26', '2022-09-26'),
    (N'Любомир', N'Мицев', '4087846897', N'Пловдив', N'улица Индустриална 30', '+359 457153111', 'lubomirmitsev@google.co', '2021-11-24', '2022-11-24'),
    (N'Марк', N'Кружков', '6287852334', N'Пловдив', N'улица Добро поле 26', '+359 388686563', 'markkruzhkov@outlook.bg', '2021-09-01', '2022-09-01'),
    (N'Васил', N'Ляляков', '8581714625', N'Пловдив', N'улица Искър 31', '+359 473336257', 'vasillyalyakov@protonmail.org', '2019-04-11', '2020-04-11'),
    (N'Олексий', N'Балев', '6858178121', N'София', N'улица Костенец 2', '+359 379333071', 'alexeybalev@outlook.bg', '2019-04-12', '2020-04-12'),
    (N'Ани', N'Бейбутян', '3702357214', N'Пловдив', N'улица Милин Камък 13', '+359 554228164', 'anibeibutyan@yahoo.org', '2019-08-22', '2020-08-22'),
    (N'Петър', N'Петров', '5435521684', N'Варна', N'улица Йосиф Цанков 26', '+359 951255637', 'peterpetrov@abv.org', '2018-08-05', '2019-08-05'),
    (N'Виктор', N'Димитров', '1788854508', N'Пловдив', N'улица Динко Петров 20', '+359 438423135', 'victordimitrov@protonmail.bg', '2021-07-05', '2022-07-05'),
    (N'Александър', N'Цонев', '9341710357', N'София', N'улица Зора 22', '+359 311900865', 'alexandertsonev@protonmail.co', '2021-10-31', '2022-10-31'),
    (N'Васил', N'Боцев', '1042361967', N'София', N'улица Черешово топче 24', '+359 629567031', 'vasilbotsev@google.org', '2018-11-19', '2019-11-19'),
    (N'Иван', N'Пенев', '6662826679', N'Варна', N'улица Бдин 18', '+359 135411882', 'ivanpenev@abv.com', '2021-09-06', '2022-09-06'),
    (N'Деляна', N'Райкова', '3547775485', N'Пловдив', N'улица Искър 29', '+359 071458827', 'delianaraykova@yahoo.co', '2019-10-12', '2020-10-12'),
    (N'Димана', N'Вятрова', '4781185660', N'София', N'улица Златен клас 4', '+359 538668284', 'dimanavyatrova@outlook.com', '2020-11-27', '2021-11-27'),
    (N'Берна', N'Ахад', '6548644444', N'Пловдив', N'улица Черноризец Храбър 17', '+359 494437298', 'bernaahad@abv.bg', '2018-08-30', '2019-08-30'),
    (N'Даниела', N'Бадева', '5911102857', N'София', N'улица Княгиня Клементина 10', '+359 732959444', 'danielabadeva@google.co', '2020-05-28', '2021-05-28'),
    (N'Калоян', N'Йонов', '2228235665', N'Пловдив', N'улица Васил Друмев 14', '+359 008220830', 'kaloyanyonov@icloud.org', '2018-09-05', '2019-09-05'),
    (N'Радослав', N'Велков', '6441533634', N'Пловдив', N'улица Димитър Димов 19', '+359 616835979', 'radoslavvelkov@google.org', '2018-05-09', '2019-05-09'),
    (N'Тина', N'Томова', '1008740428', N'Варна', N'улица Стоян Михайловски 28', '+359 378872536', 'tinatomova@yahoo.co', '2019-03-09', '2020-03-09'),
    (N'Стефан', N'Велев', '1382495352', N'София', N'улица Иларион Драгостинов 22', '+359 356515053', 'stefanvelev@google.co', '2018-07-15', '2019-07-15'),
    (N'Момчил', N'Занев', '2981541767', N'Пловдив', N'улица Цар Самуил 10', '+359 687734251', 'boyzanev@abv.org', '2019-08-07', '2020-08-07'),
    (N'Рая', N'Симеонова', '7172354632', N'София', N'булевард Черни връх 17', '+359 204895125', 'rayasimeonova@outlook.co', '2021-05-17', '2022-05-17'),
    (N'Владимир', N'Радев', '7411337645', N'София', N'улица Жеко Георгиев 32', '+359 637323390', 'vladimirradev@yahoo.org', '2020-02-18', '2021-02-18'),
    (N'Йоан', N'Бабулков', '3428194744', N'Варна', N'улица Люлинска 21', '+359 463584675', 'johnbabulkov@abv.org', '2021-04-20', '2022-04-20'),
    (N'Цветелина', N'Чакърова', '1183744476', N'Пловдив', N'улица Акация 30', '+359 832787954', 'tsvetelinachakarova@google.bg', '2019-01-29', '2020-01-29'),
    (N'Лъчезар', N'Кеманов', '7466979182', N'София', N'улица Букет 34', '+359 731142655', 'lachezarkemanov@yahoo.org', '2021-05-11', '2022-05-11'),
    (N'Коста', N'Димитров', '5341744607', N'Пловдив', N'улица Гривица 1', '+359 251776946', 'kostadimitrov@yahoo.com', '2018-11-28', '2019-11-28'),
    (N'Мария', N'Кукова', '8573688164', N'Пловдив', N'улица Лозарска 32', '+359 550812112', 'mariakukova@protonmail.co', '2018-02-18', '2019-02-18'),
    (N'Дарина', N'Даилова', '2175816009', N'Варна', N'улица Стоил Войвода 25', '+359 439450675', 'darinadailova@protonmail.com', '2020-10-29', '2021-10-29'),
    (N'Дейвид', N'Каменов', '0787367577', N'Пловдив', N'улица Опълченска 27', '+359 324135434', 'davidkamenov@outlook.bg', '2021-12-05', '2022-12-05'),
    (N'Иван', N'Досев', '3544664646', N'Пловдив', N'улица Здравец 23', '+359 262938295', 'ivandosev@outlook.co', '2021-10-24', '2022-10-24'),
    (N'Александра', N'Радева', '8752434672', N'София', N'улица Еделвайс 19', '+359 162641521', 'alexandraradeva@outlook.com', '2019-04-02', '2020-04-02'),
    (N'Павел', N'Атанасов', '7422155623', N'София', N'улица Пирин 8', '+359 417246511', 'pavelatanasov@abv.org', '2021-12-19', '2022-12-19'),
    (N'Антон', N'Пашов', '4504825861', N'Пловдив', N'улица Шести май 7', '+359 461551233', 'antonpashov@icloud.org', '2021-09-27', '2022-09-27'),
    (N'Александър', N'Маринов', '3240469414', N'София', N'улица Бачо Киро 28', '+359 608175913', 'alexandermarinov@icloud.bg', '2021-08-06', '2022-08-06'),
    (N'Юсмен', N'Забанов', '5288214415', N'Варна', N'улица Редута 19', '+359 735030131', 'yusmenzabanov@outlook.bg', '2019-10-17', '2020-10-17'),
    (N'Айлин', N'Усенджикова', '8911239373', N'София', N'улица Никола Палаузов 16', '+359 551236610', 'ailenusendikova@yahoo.com', '2021-04-09', '2022-04-09'),
    (N'Лияна', N'Асенова', '4217167254', N'София', N'улица Солунска 9', '+359 705445007', 'lianaasenova@outlook.org', '2018-10-21', '2019-10-21'),
    (N'Емилиан', N'Спасов', '1856814895', N'Варна', N'улица Лебед 18', '+359 348802327', 'emilianspasov@abv.co', '2022-04-07', '2023-04-07'),
    (N'Даниела', N'Дишлянова', '4287212635', N'София', N'улица Георги Велев 29', '+359 674573102', 'danieladishlyanova@icloud.com', '2018-07-14', '2019-07-14'),
    (N'Моника', N'Митрева', '5526640520', N'Варна', N'улица Шипка 18', '+359 336447644', 'monicamitreva@abv.co', '2019-07-18', '2020-07-18'),
    (N'Алекс', N'Георгиев', '5538003652', N'Пловдив', N'булевард Велико Търново 27', '+359 692558744', 'alexgeorgiev@outlook.bg', '2020-01-30', '2021-01-30'),
    (N'Емил', N'Цанев', '6737614989', N'Пловдив', N'улица Хаджи Димитър 19', '+359 402409151', 'emiltsanev@google.bg', '2021-07-26', '2022-07-26'),
    (N'Дуйгу', N'Хасан', '4096325299', N'Варна', N'улица Костенец 33', '+359 993389844', 'doughasan@yahoo.org', '2019-03-28', '2020-03-28'),
    (N'Даниел', N'Халачев', '7321102058', N'Варна', N'улица Тутракан 7', '+359 574878701', 'danielhalachev@icloud.com', '2020-03-11', '2021-03-11'),
    (N'Десислава', N'Белчева', '9600256154', N'Пловдив', N'улица Охрид 18', '+359 176491566', 'desislavabelcheva@outlook.co', '2021-05-06', '2022-05-06'),
    (N'Павла', N'Манова', '1612322887', N'София', N'улица Славчо Красински 4', '+359 340236148', 'pavelmanov@google.com', '2021-07-22', '2022-07-22'),
    (N'Васил', N'Любенов', '4875477613', N'Пловдив', N'улица Тодор Миланович 17', '+359 082698328', 'vasillyubenov@yahoo.co', '2019-08-19', '2020-08-19'),
    (N'Илиян', N'Йорданов', '8558980488', N'София', N'улица Атанас Николов 34', '+359 223248158', 'ilianyordanov@protonmail.org', '2021-09-07', '2022-09-07'),
    (N'Саня', N'Севдева', '9345847615', N'Варна', N'улица Дванадесета 28', '+359 665212307', 'sanyasevdeva@icloud.bg', '2018-04-16', '2019-04-16'),
    (N'Петър', N'Атанасов', '2417547386', N'София', N'улица Желязко Петков 3', '+359 639681458', 'petaratanasov@yahoo.bg', '2018-03-12', '2019-03-12'),
    (N'Илия', N'Петров', '7325665956', N'София', N'улица Алеко Туранджа 14', '+359 177047886', 'iliyapetrov@yahoo.bg', '2019-05-15', '2020-05-15'),
    (N'Любомир', N'Стойков', '7972558271', N'София', N'улица Георги С.Раковски 30', '+359 583138233', 'lubomirstoykov@protonmail.com', '2022-04-11', '2023-04-11'),
    (N'Анета', N'Цветкова', '4106143296', N'Варна', N'улица Ключ 14', '+359 661655847', 'anetatsvetkova@yahoo.co', '2018-08-22', '2019-08-22'),
    (N'Ива', N'Бошнакова', '7894643756', N'Пловдив', N'улица Георги Данчов 4', '+359 317148677', 'ivaboshnakova@protonmail.bg', '2022-01-16', '2023-01-16'),
    (N'Назифе', N'Алиджик', '0479667680', N'Пловдив', N'улица Шести септември 31', '+359 562399366', 'nazifealijik@abv.org', '2019-02-27', '2020-02-27'),
    (N'Силвия', N'Димитрова', '0073773118', N'Пловдив', N'улица Доктор Борис Божков 12', '+359 258871552', 'silviadimitrova@protonmail.com', '2020-02-23', '2021-02-23'),
    (N'Калин', N'Цветков', '5141687772', N'София', N'улица Гергана 33', '+359 865771252', 'kalintsvetkov@yahoo.bg', '2020-12-07', '2021-12-07'),
    (N'Михаил', N'Зонев', '0775738054', N'Пловдив', N'улица Борис Христов 33', '+359 241106034', 'mikhailzonev@icloud.bg', '2018-11-22', '2019-11-22'),
    (N'Лъчезар', N'Цветков', '5264647231', N'Пловдив', N'улица Стоян Илиев 24', '+359 027630725', 'lachezartsvetkov@google.bg', '2019-03-10', '2020-03-10'),
    (N'Сияна', N'Тодорова', '5889675255', N'София', N'улица Братя Миладинови 15', '+359 815473792', 'siyanatodorova@icloud.com', '2020-05-14', '2021-05-14'),
    (N'Михаела', N'Илиева', '6641812644', N'Пловдив', N'улица Генерал Дандевил 12', '+359 665762841', 'michaelailieva@yahoo.co', '2020-04-09', '2021-04-09'),
    (N'Никол', N'Казанджиева', '5918243959', N'София', N'улица Свети Свети Кирил и Методий 9', '+359 044570268', 'nicolekazandzhieva@icloud.com', '2018-03-26', '2019-03-26'),
    (N'Елисавета', N'Дочева', '2651683370', N'София', N'улица Опълченска 5', '+359 762568941', 'elisavetadocheva@outlook.co', '2019-03-18', '2020-03-18'),
    (N'Никола', N'Михайлов', '3388631821', N'София', N'улица Уста Генчо Кънев 25', '+359 616431886', 'nikolamikhailov@google.bg', '2019-08-01', '2020-08-01'),
    (N'Мая', N'Методиева', '4290737080', N'Пловдив', N'улица Младост 8', '+359 585856558', 'mayametodieva@outlook.com', '2022-02-07', '2023-02-07'),
    (N'Стефания', N'Цветкова', '6880051668', N'София', N'улица Охрид 14', '+359 482873638', 'stefaniatsvetkova@outlook.co', '2021-05-31', '2022-05-31'),
    (N'Огнян', N'Йончев', '9865984263', N'София', N'улица Пирин 34', '+359 533682815', 'ognyanyonchev@yahoo.com', '2020-04-20', '2021-04-20'),
    (N'Симеон', N'Йорданов', '9282474102', N'Пловдив', N'улица Стефан Стамболов 19', '+359 642786352', 'simeonyordanov@abv.bg', '2019-10-19', '2020-10-19')
GO

INSERT INTO [Library].[dbo].[ReadersBlacklist]
    ([ReaderID], [From], [To], [Reason])
VALUES
    (6, '2018-02-05', '2019-02-05', 'Не спазва тишина в библиотеката')
GO

INSERT INTO [Library].[dbo].[Rentals]
    ([ID], [ReaderID], [BookCopyID], [From], [To], [Comment])
VALUES
    (NEWID(), '1', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=1) AS record
        WHERE rownumber=1), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=1)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=1)), NULL),
    (NEWID(), '2', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=2) AS record
        WHERE rownumber=1), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=2)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=2)), NULL),
    (NEWID(), '3', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=1) AS record
        WHERE rownumber=2), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=3)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=3)), NULL),
    (NEWID(), '4', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=1) AS record
        WHERE rownumber=3), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=4)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=4)), NULL),
    (NEWID(), '5', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=2) AS record
        WHERE rownumber=2), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=5)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=5)), NULL),
    (NEWID(), '6', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=2 AND NOT EXISTS (SELECT
                    1
                FROM
                    Rentals
                WHERE BookCopyID = BookCopies.ID)) AS record
        WHERE rownumber=1), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=6)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=6)), NULL),
    (NEWID(), '9', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=3) AS record
        WHERE rownumber=1), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=9)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=9)), NULL),
    (NEWID(), '13', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=2) AS record
        WHERE rownumber=3), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=13)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=13)), NULL),
    (NEWID(), '14', (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS rownumber,
                ID
            FROM
                [Library].[dbo].[BookCopies]
            WHERE BookCopies.BranchID=3) AS record
        WHERE rownumber=2), DATEADD(DAY, 1, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=14)), DATEADD(DAY, 31, (SELECT
            Readers.Joined
        FROM
            Readers
        WHERE Readers.ID=14)), NULL)        
GO

INSERT INTO [Library].[dbo].[Returns]
    ([RentalID], [ReturnDate], [Damage])
VALUES
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=1),
        DATEADD(day, 1, (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=1)), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=2),
        DATEADD(day, -5, (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=2)), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=3),
        (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=3), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=4),
        DATEADD(day, 20, (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=4)), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=5),
        (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=5), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=6),
        DATEADD(day, -3, (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=6)), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=7),
        DATEADD(day, 10, (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=7)), NULL),
    (
        (SELECT
            ID
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=8),
        (SELECT
            [To]
        FROM
            (SELECT
                ROW_NUMBER() OVER (ORDER BY [ID] ASC) AS [rownumber],
                [ID],
                [To]
            FROM
                [Library].[dbo].[Rentals]) AS record
        WHERE rownumber=8), NULL)
GO