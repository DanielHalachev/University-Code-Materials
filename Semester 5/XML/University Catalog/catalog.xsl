<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <xsl:template match="/">
        <html>            
            <head>
                <title>Каталог на университетите в България</title>
                <script src="script.js"></script>
                <script src="https://ajax.googleapis.com/ajax/libs/webfont/1.4.7/webfont.js"></script>
                <link rel="stylesheet" type="text/css" href="style.css" />
            </head>
            
            <body onload="main()">
                <header>
                    <h1 id="logo">Каталог на университетите в <span id="bg">България</span></h1>                    
                    <nav>
                        <ul class="nav-links">
                            <li id="overviewButton"><a onclick="showOverview()">Общ преглед</a></li>
                            <li id="regionsButton"><a onclick="showRegions()">Региони</a></li>
                            <li id="detailsButton"><a onclick="showDetails()">Детайли</a></li>
                        </ul>
                    </nav>
                </header>
                
                <div id="content">
                    <div id="overview">            
                        <xsl:for-each select="/catalog/universities/university">
                            <xsl:variable name="addr">
                                <xsl:value-of select="self::node()/image/@src"/>
                            </xsl:variable>
                            <div class="uni">
                                <img>
                                    <xsl:attribute name="src">images/<xsl:value-of select="$addr"/></xsl:attribute>
                                    <xsl:attribute name="alt">images/<xsl:value-of select="$addr"/></xsl:attribute>
                                </img>                                
                                <h2><xsl:value-of select="name"/></h2>
                                <div class="info">
                                    <p>
                                        <span><b>Ректор: </b></span>
                                        <span><xsl:value-of select="chancellor"/></span>
                                    </p>
                                    <p>
                                        <span><b>Дата на създаване: </b></span>
                                        <span><xsl:value-of select="statistics/since"/></span>
                                    </p>
                                    <p>
                                        <span><b>Брой студенти: </b></span>
                                        <span><xsl:value-of select="statistics/students"/></span>
                                    </p>
                                    <p>
                                        <span><b>Брой преподаватели: </b></span>
                                        <span><xsl:value-of select="statistics/lecturers"/></span>
                                    </p>
                                </div>
                            </div>
                        </xsl:for-each>        
                    </div>        
                    <xsl:apply-templates/>
                </div>
            </body>        
        </html>
    </xsl:template>    
    <xsl:template match="/catalog/regions">
        <div id="regions">
            <xsl:for-each select="/catalog/regions/region">
                <xsl:variable name="regName"><xsl:value-of select="self::node()"/></xsl:variable>
                <xsl:variable name="regID"><xsl:value-of select="self::node()/@id"/></xsl:variable>
                
                <h1 class="collapsable"><xsl:value-of select="$regName"/> регион</h1>
                <div class="uni-collapsable">                    
                    <xsl:for-each select="/catalog/universities/university[@regionID=$regID]">
                        <xsl:variable name="addr">
                            <xsl:value-of select="self::node()/image/@src"/>
                        </xsl:variable>
                        <div class="uni"> 
                            
                            <img>
                                <xsl:attribute name="src">images/<xsl:value-of select="$addr"/></xsl:attribute>
                                <xsl:attribute name="alt">images/<xsl:value-of select="$addr"/></xsl:attribute>
                            </img>
                            <h2><xsl:value-of select="name"/></h2>
                            <div class="info">
                                <p>
                                    <span><b>Ректор: </b></span>
                                    <span><xsl:value-of select="chancellor"/></span>
                                </p>
                                <p>
                                    <span><b>Дата на създаване: </b></span>
                                    <span><xsl:value-of select="statistics/since"/></span>
                                </p>
                                <p>
                                    <span><b>Брой студенти: </b></span>
                                    <span><xsl:value-of select="statistics/students"/></span>
                                </p>
                                <p>
                                    <span><b>Брой преподаватели: </b></span>
                                    <span><xsl:value-of select="statistics/lecturers"/></span>
                                </p>
                            </div>
                        </div> 
                    </xsl:for-each>
                </div>
                
            </xsl:for-each>
        </div>
    </xsl:template>
    
    <xsl:template match="/catalog/universities">
        <div id="table">
            <input type="text" id="searchBox" onkeyup="searchTable()" placeholder="Търсете име на университет..."/>
            <table id="myTable">
                <tr>
                    <th onclick="sortTable(0)">Име</th>
                    <th onclick="sortTable(1)">Регион</th>
                    <th onclick="sortTable(2)">Град</th>
                    <th onclick="sortTable(3)">Адрес</th>
                    <th onclick="sortTable(4)">Контакти</th>
                    <th onclick="sortTable(5)">Студенти<br/>Преподаватели</th>
                    <th onclick="sortTable(6)">Факултети</th>
                </tr>
                
                <xsl:for-each select="/catalog/universities/university">
                    <xsl:variable name="regID"><xsl:value-of select="self::node()/@regionID"/></xsl:variable>
                    
                    <tr>
                        <td><xsl:value-of select="name"/></td>
                        <td><xsl:value-of select="/catalog/regions/region[@id=$regID]"/></td>
                        <td><xsl:value-of select="location/city"/></td>
                        <td><xsl:value-of select="location/address"/></td>
                        <td>
                            <xsl:for-each select="contacts/*">
                                <p><xsl:value-of select="self::node()"/></p>
                            </xsl:for-each>
                        </td>
                        <td>
                            <p><xsl:value-of select="statistics/students"/></p>
                            <br/>
                            <p><xsl:value-of select="statistics/lecturers"/></p>
                        </td>
                        <td>
                            <h4 class="collapsableFaculties">Покажи факултетите</h4>
                            <div class="facs">
                                <xsl:for-each select="faculties/faculty">
                                    <p><xsl:value-of select="self::node()"/></p>
                                </xsl:for-each>
                            </div>
                        </td>
                    </tr>
                </xsl:for-each>
            </table>
        </div>        
    </xsl:template>
</xsl:stylesheet>