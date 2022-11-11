<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <body>
                <h2>My CD Collection</h2>
                <table border="1">
                    <tr bgcolor="#9acd32">
                        <th align="left">Title</th>
                        <th align="left">Artist</th>
                        <th align="left">Year</th>
                        <th align="left">Category</th>
                        <th align="left">ID</th>
                    </tr>
                    <xsl:for-each select="catalog/cd">
                        <tr>
                            <td><xsl:value-of select="title"/></td>
                            <td><xsl:value-of select="artist"/></td>
                            <td><xsl:value-of select="year"/></td>
                            <td><xsl:value-of select="./@category"/></td>
                            <td><xsl:value-of select="./@id"/></td>
                        </tr>
                        <tr>
                            <td>
                                <xsl:for-each select="tracklist/track">
                                    <li><xsl:value-of select="text()"/></li>
                                </xsl:for-each>
                            </td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>