/* Archivo fuente para el analizador léxico de flex*/

/* Dividimos en 4 partes el código para flex */

/*Includes*/
%{
#include <string.h>
#include <math.h>


#include "interpreteMat.h"
#include "tablaSimbolos.h"
#include "bison.tab.h"
#define MAX_STR_CONST 500
%}

/*Se indica que solo se leera un fichero de entrada.*/
/*Se crea un fichero .h lex.yy.h y que no tendremos funciones input ni yyunput*/
/*Esas dos últimas son para evitar warnings*/
%option noyywrap header-file="lex.yy.h" noinput nounput

/*Definiciones*/
/*Aqui definimos los diferentes lexemas que se puede encontrar el analizador en formate nombre definicion por ejemplo DIGITO [0-9]*/

LETTER              [a-zA-Z]|_

DECIMAL_DIGIT       [0-9]
DIGITS              {DECIMAL_DIGIT}(\_?{DECIMAL_DIGIT})*

EXPONENT            [eE][\+|\-]?{DIGITS} 

ENTERO              {DIGITS}
DECIMAL             {DIGITS}\.{DIGITS}?{EXPONENT}?|{DIGITS}{EXPONENT}|\.{DIGITS}{EXPONENT}?

/* Comentarios */
LINE_COMMENT         \/\/[^\n]*      
GENERAL_COMMENTS     \/\*([^*]|(\*+[^*/]))*\*+\/     

/* Componentes lexicos */

IGNORAR             [ \t]

IDENTIFIER          ({LETTER}|\_)({LETTER}|{DECIMAL_DIGIT}|\_)*

INDIVIDUAL          [+\-\*/%&\|^<>=!~([{,\.)\]};:\n\r]

NUMERO              {ENTERO}|{DECIMAL}

FICHERO             ({LETTER}|{DECIMAL_DIGIT})+(\.({LETTER}|{DECIMAL_DIGIT})+)+|(\/({LETTER}|{DECIMAL_DIGIT})*)*\/({LETTER}|{DECIMAL_DIGIT})+(\.({LETTER}|{DECIMAL_DIGIT})+)+

/* Declaramos la función que se usará para contabilizar cuantos comentarios se abren */
%x NESTED_COMMENT 

    int comment_nesting = 0; /*contador de comentarios anidados abiertos*/

/*Reglas*/
%%

{IGNORAR}
{LINE_COMMENT}
{GENERAL_COMMENTS}

"/+"                { BEGIN(NESTED_COMMENT); }
    <NESTED_COMMENT>{
    "/+"            { comment_nesting++;} /*si econtramos una apertura, si no es la primera, sumaremos 1 al contador, si es la primera, se inicia esta funcion*/
    "+"+"/"         { if(comment_nesting) comment_nesting--; /*Si enconrtamos una cadena +/ tendremos que restarle 1 al contador, y si es 0 volver al estado incial*/
                        else BEGIN(INITIAL); }
    "+"+            ; /*Se ignoran las cadenas de + seguidos*/
    [^/+\n]+        ; /* Aqui entran todos los caracteres que no sean /+ o \n, de manera que se ignoren */
    [/]             ; /*Ignoramos toda barra que no vaya acompañada de un +*/
    \n              ; /*Ignoramos todos los saltos de linea*/
    /*Se elaboran reglas separadas, porque con una sola regla se descrubrió que no funcionaba del todo bien, asi que, tras investigar en diferentes páginas, esta fue la combinación que encontré para que funcionara correctamente*/
}


{IDENTIFIER}        {
                        yylval.cadena = strdup(yytext);
                        CompLexico comp = buscarLexema(yylval.cadena);
                        if (comp.lexema == NULL) {
                            return VAR;
                        }
                        return comp.valorLexico;
                    }
{NUMERO}            { 
                        yylval.numero = atof(yytext); 
                        return NUM; 
                    }
{INDIVIDUAL}        return (int) *yytext;
{FICHERO}           yylval.cadena = strdup(yytext); return FICHERO;

.                  printf(ROJO"LEXEMA DESCONOCIDO"RESET"\n\n");

<<EOF>>		        ejecutandoScript(0); fclose(yyin); yyrestart(stdin);

%%