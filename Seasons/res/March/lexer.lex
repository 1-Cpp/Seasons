
LEX = {
COMMENT=#
delimiterChar=+*:=|-[]^
beginChar='
beginString="
escapeChar=\
stringChar^=\'"
upper[]=A-Z
lower[]=a-z
whiteChar\=\t \n\v\f
whitespace:=whiteChar+
identifierChar:=upper|lower
identifier:=identifierChar+
delimiter:=delimiterChar
charDef:=beginChar [ stringChar | escapeChar beginChar ]* stringChar beginChar
stringMiddle:=[ stringChar | escapeChar beginString | escapeChar stringChar | escapeChar beginChar | escapeChar escapeChar ]
stringDef:=beginString stringMiddle* stringChar beginString
EXPORT:=identifier delimiter charDef stringDef EOS
}
