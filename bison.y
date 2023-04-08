%{
#include <math.h>

#include "lex.yy.h"
#include "tablaSimbolos.h"

CompLexico comp;
/*Flags para el interprete, de manera que sepa que hacer*/
int doEcho = 1;
int script = 0;
int error = 0;

void yyerror (char *s);
%}

/*declaraciones bison*/

%union{
    double numero;
    char *cadena;
}

%start entrada

/*TOKEN*/
%token <numero> NUM
%token <cadena> CONS VAR FUNC CMND0 CMND1 FICHERO LIB

%type <numero> exp asig cmnd

%left '-' '+'
%left '*' '/'
%left '%'
%precedence NEG
%right '^'

%%

entrada: %empty         {
                            if(!script){
                                printf(CYAN">"RESET" ");
                            }
                        }
        | entrada linea
;

linea:  '\n'                { printf(CYAN">"RESET" "); }
       | exp '\n'           {
                                if (!error) {
                                    if(isnan($1)){
                                        printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | exp ';' '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | asig '\n'           {
                                if (!error) {
                                    if(isnan($1)){
                                        printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | asig ';' '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | cmnd '\n'         {
                                if(isnan($1) && !error){
                                    printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                }
                                if(!script){
                                    printf(CYAN">"RESET" ");
                                }
                                error = 1;
                            }
        | cmnd ';' '\n'     {
                                if(isnan($1) && !error){
                                    printf(ROJO"NAN DETECTADO"RESET"\n\n");printf("NAN DETECTADO");
                                }
                                if(!script){
                                    printf(CYAN">"RESET" ");
                                }
                                error = 1;
                            }
;

exp:    NUM
        | CONS              {
                                comp = buscarLexema($1);
                                $$ = comp.valor.var;
                                free($1);
                            }
        | VAR               {
                                comp = buscarLexema($1);
                                if(comp.lexema != NULL){
                                    $$ = comp.valor.var;
                                }else{
                                    printf(ROJO"VARIABLE NO DEFINIDA"RESET"\n\n");
                                    error = 1;
                                    $$ = NAN;
                                }
                                free($1);
                            }
        | '-' exp %prec NEG {
                                if(!isnan($2)){
                                    $$ = -$2;
                                }else{
                                    $$ = NAN;
                                }
                            }
        | exp '+' exp       {
                                if(!isnan($1) && !isnan($3)){
                                    $$ = $1 + $3;
                                }else{
                                    $$ = NAN;
                                }
                            }
        | exp '-' exp       {
                                if(!isnan($1) && !isnan($3)) {
                                    $$ = $1 - $3;
                                }else{
                                    $$ = NAN;
                                }
                            }
        | exp '*' exp       {
                                if(!isnan($1) && !isnan($3)) {
                                    $$ = $1 * $3;
                                }else{
                                    $$ = NAN;
                                }
                            }
        | exp '/' exp   {
                            if ($3 == 0) {
                                printf(ROJO"Division por 0, ERROR"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                            } else {
                                if (!isnan($1) && !isnan($3)) {
                                    $$ = $1 / $3;
                                } else {
                                    $$ = NAN;
                                }
                            }
                        }
        | exp '%' exp   {
                            if ($3 == 0) {
                                printf(ROJO"MODULO CERO. ERROR!"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                            } else {
                                if (!isnan($1) && !isnan($3)) {
                                    $$ = fmod($1, $3);
                                } else {
                                    $$ = NAN;
                                }
                            }
                        }
        | exp '^' exp       {
                                if(!isnan($1) && !isnan($3)) {
                                    $$ = pow($1, $3);
                                }else{
                                    $$ = NAN;
                                }
                            }
        | '(' exp ')'       {
                                if(!isnan($2)) {
                                    $$ = $2;
                                }else{
                                    $$ = NAN;
                                }
                            }
;

asig:   VAR '=' exp         {
                                if (!error) {
                                    comp = buscarLexema($1);
                                    if (comp.lexema != NULL) {
                                        modificarValorVariable($1, $3);
                                    } else {
                                        comp.lexema = strdup($1);
                                        comp.valorLexico = VAR;
                                        comp.valor.var = $3;
                                        insertarComponente(comp);
                                        free(comp.lexema);
                                    }
                                }
                                $$ = $3;
                                free($1);
                            }
        
        | CONS   '=' exp    {
                                printf(ROJO"Las constantes no se pueden modificar"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                                free($1);
                            }
;

cmnd:   CMND0               {
                                comp = buscarLexema($1);
                                free($1);
                                (*(comp.valor.funcptr))();
                            }
        | CMND0 '(' ')'     {
                                comp = buscarLexema($1);
                                free($1);
                                (*(comp.valor.funcptr))();
                            }
        | CMND1             {
                                printf(ROJO"Fihcero no identifado"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                                free($1);
                            }  
        | CMND1 '(' ')'     {
                                printf(ROJO"Fihcero no identifado"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                                free($1);
                            } 
        | CMND1 FICHERO     {
                                comp = buscarLexema($1);
                                (*(comp.valor.funcptr))($2);
                                free($1);
                                free($2);
                            }  
        | CMND1 '(' FICHERO ')' {
                                comp = buscarLexema($1);
                                (*(comp.valor.funcptr))($3);
                                free($1);
                                free($3);
                            }
        | CMND1 exp         {
                                printf(ROJO"MAL FORMATO DE FICHERO"RESET"\n\n");
                                error = 1;
                                $$ = NAN;
                                free($1);
                            }
;

%%
void yyerror(char *s) {
    printf("SINTAXIS NO VALIDA\n");
}

void cambiarEcho(int valor) {
    doEcho = valor;
    if (doEcho) { 
        printf(VERDE"Echo activado."RESET"\n\n");
    }else{
        printf(ROJO"Echo desactivado."RESET"\n\n");
    }
}

void ejecutandoScript(int valor) {
    script = valor;
    if (!script) {
        printf("\n"AMARILLO"Script ejecutado correctamente."RESET"\n\n"CYAN">"RESET" ");
    }
}