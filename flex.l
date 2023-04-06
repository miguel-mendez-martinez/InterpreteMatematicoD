/* Archivo fuente para el analizador léxico de flex*/

/* Dividimos en 4 partes el código para flex */

/*Includes*/
%{
#include "definiciones.h"
#include "tablaSimbolos.h"
#define MAX_STR_CONST 500
%}

/*Se indica que solo se leera un fichero de entrada, que se llevará una cuenta*/
/*Se crea un fichero .h lex.yy.h y que no tendremos funciones input ni yyunput*/
/*Esas dos últimas son para evitar warnings*/
%option noyywrap yylineno header-file="lex.yy.h" noinput nounput

/*Definiciones*/
/*Aqui definimos los diferentes lexemas que se puede encontrar el analizador en formate nombre definicion por ejemplo DIGITO [0-9]*/

LETTER              [a-zA-Z]

DECIMAL_DIGIT       [0-9]
DECIMAL_DIGITS      {DECIMAL_DIGIT}(\_?{DECIMAL_DIGIT})*
BINARY_DIGIT        [01]
BINARY_DIGITS       {BINARY_DIGIT}(\_?{BINARY_DIGIT})*

DECIMAL_LIT         [0-9](\_?{DECIMAL_DIGITS})?
BINARY_LIT          0[bB]\_?{BINARY_DIGITS}

DECIMAL_EXPONENT    [eE][\+|\-]?{DECIMAL_DIGITS}

DECIMAL_FLOAT_LIT   {DECIMAL_DIGITS}\.{DECIMAL_DIGITS}?{DECIMAL_EXPONENT}?|{DECIMAL_DIGITS}{DECIMAL_EXPONENT}|\.{DECIMAL_DIGITS}{DECIMAL_EXPONENT}?

/* Comentarios */
LINE_COMMENT         \/\/[^\n]*      
GENERAL_COMMENTS     \/\*([^*]|(\*+[^*/]))*\*+\/     

/* Componentes lexicos */

IGNORAR             [ \t\r\n]

IDENTIFIER          ({LETTER}|\_)({LETTER}|{DECIMAL_DIGIT}|\_)*

INDIVIDUAL          [+\-\*/%&\|^<>=!~([{,\.)\]};:]

/* Operadores */
_MENORQUE           <<
_MAYORQUE           >>
_SUMAIGUAL          \+=
_RESTAIGUAL         -=
_MULTIGUAL          \*=
_DIVIGUAL           \/=
_AMPERDOBLE         &&
_SUMADOBLE          \+\+
_RESTADOBLE         --
_IGUALDOBLE         ==
_EXCLAMACIONIGUAL   !=
_MENORIGUAL         <=
_MAYORIGUAL         >=

_INT                ({DECIMAL_LIT}|{BINARY_LIT})
_FLOAT              {DECIMAL_FLOAT_LIT}

_STRING             `(.|\n)*`|\"([^\"\\\n]|(\\.))*\"


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

{IDENTIFIER}        return ID;

{INDIVIDUAL}        return (int) *yytext;
{_MENORQUE}         return MENORQUE;
{_MAYORQUE}         return MAYORQUE;
{_SUMAIGUAL}        return SUMAIGUAL;
{_RESTAIGUAL}         return RESTAIGUAL;
{_MULTIGUAL}          return MULTIGUAL;
{_DIVIGUAL}           return DIVIGUAL;
{_AMPERDOBLE}         return AMPERDOBLE;
{_SUMADOBLE}          return SUMADOBLE;
{_RESTADOBLE}         return RESTADOBLE;
{_IGUALDOBLE}         return IGUALDOBLE;
{_EXCLAMACIONIGUAL}   return EXCLAMACIONIGUAL;
{_MENORIGUAL}         return MENORIGUAL;
{_MAYORIGUAL}         return MAYORIGUAL;

{_INT}                return INT;
{_FLOAT}              return FLOAT;

{_STRING}             return STRING;

<<EOF>>		yyterminate();

%%

/*Codigo Usuario*/

void iniciarAnalizadorLexico(char *nomeFicheiro){
    yyin = fopen(nomeFicheiro, "r");
    if (yyin == NULL) {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }

    // Para que en caso de detectar un erro léxico non imprima os caracteres pendentes de procesar:
    yyout = fopen("/dev/null", "w");
}

void sigCompLexico(tipoelem *compLex) {
    if (compLex->identificador != NULL) {
        free(compLex->identificador);
        compLex->valor = 0;
        compLex->identificador = NULL;
    }

    compLex->valor = yylex();
    compLex->identificador = malloc((yyleng + 1) * sizeof(char));
    strcpy(compLex->identificador, yytext);
    compLex->identificador[yyleng] = '\0';

    if(compLex->valor == ID){
        buscaElemento(compLex);
    }

    if(compLex->valor == 0){
        compLex->valor = EOF;
    }

}

void finalizarAnalizadorLexico(tipoelem *compLex) {
    if (compLex->identificador != NULL) {
        free(compLex->identificador);
        compLex->valor = 0;
        compLex->identificador = NULL;
    }

    fclose(yyin);
    fclose(yyout);
	yylex_destroy();
}