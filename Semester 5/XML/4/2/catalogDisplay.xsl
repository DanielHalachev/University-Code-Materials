<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
            <head>
                <meta charset="utf-8"/>
            </head>
            <body>
                <!-- 1 -->
                <!-- <xsl:for-each select="catalog/cd[@id='8c0a600b']/tracklist/track[@length='4:04']">
                     <xsl:value-of select="."/>
                     </xsl:for-each> -->
                
                <!-- 2 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[position() mod 2=0]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 3 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[string-length(.)>35]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 4 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[string-length(.)>35]">
                     <xsl:value-of select="string-length(.)"/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 5 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[last()]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 6 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[position()=5]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 7 -->          
                <!-- <xsl:for-each select="catalog/cd/tracklist">
                     <xsl:value-of select="count(track)"/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 8 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[contains(text(), 'Ya soshla s uma')]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 9 breaks-->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[matches(text(), '^D*')]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 10 breaks -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[matches(text(), '*sta')]">
                     <xsl:value-of select="."/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 11 breaks-->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track">
                     <xsl:value-of select="upper-case(.)"/>
                     <br/>
                     </xsl:for-each> -->
                
                <!-- 12 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/track[@length='3:55' and text()='Robot (Robotronik)']/../../year">
                     <xsl:value-of select="."/>
                     </xsl:for-each> -->
                
                <!-- 13 -->
                <!-- <xsl:for-each select="catalog/cd/tracklist/count(track) div catalog/count(cd)">
                     <xsl:value-of select="."/>
                     </xsl:for-each> -->
                
                <!-- 14 -->
                <xsl:for-each select="concat('Title: ',catalog/cd/title, '; Year:', catalog/cd/year)">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>