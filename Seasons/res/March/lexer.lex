
LEX = {
COMMENT=#
delimiter=+*:=|-[]^
beginChar='
escape=\
stringChar^=\
upper[]=A-Z
lower[]=a-z
white\=\t \n\v\f
identifierChar:=upper|lower
identifier:=identifierChar+
charDef:=beginChar [ stringChar | escape beginChar ]* stringChar beginChar
EXPORT:=identifier delimiter charDef EOS
}
