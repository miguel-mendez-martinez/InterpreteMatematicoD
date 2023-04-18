%{
#include <math.h>
#include "lex.yy.h"
#include "tablaSimbolos.h"
#include "system.h"

CompLexico comp;
CompLexico comp2;
/*Flags para el interprete, de manera que sepa que hacer*/
int doEcho = 1;
int script = 0;
int error = 0;

void yyerror (char *s);
%}

%union{
    double number;
    char *cadena;
}

%start start

%token <number> NUM
%token <cadena> CONS VAR FUNC CMND0 CMND1 LOAD FICHERO 

%type <number> expresion asig comando fnc op

%left '-' '+'
%left '*' '/'
%left '%'
%precedence NEG
%right '^'

%%
start: %empty         {
                            if(!script){
                                printf(CYAN">"RESET" ");
                            }
                        }
        | start line
;

line:  '\n'                { printf(CYAN">"RESET" "); }
        | expresion '\n'          {
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
        | expresion ';' '\n'      {
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
        | comando '\n'         {
                                if (isnan($1) && !error) {
                                    printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | comando ';' '\n'     {
                                if (isnan($1) && !error) {
                                    printf(ROJO"NAN DETECTADO"RESET"\n\n");
                                }
                                if (!script) {
                                    printf(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
;

expresion:    NUM                       { $$ = $1; }
        | CONS                          {
                                            comp = buscarLexema($1);
                                            if(comp.lexema != NULL){
                                                $$ = comp.valor.var;
                                            }else{
                                                printf(ROJO"CONSTANTE NO DEFINIDA"RESET"\n\n");
                                                error = 1;
                                                $$ = NAN;
                                            }
                                            free($1);
                                        }
        | VAR                           {
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
        | op
        | fnc 
        | '(' expresion ')'             {
                                            if(!isnan($2)) {
                                                $$ = $2;
                                            }else{
                                                $$ = NAN;
                                            }
                                        }               
;

op: 
        '-' expresion %prec NEG       {
                                            if(!isnan($2)){
                                                $$ = -$2;
                                            }else{
                                                $$ = NAN;
                                            }
                                        }
        | expresion '+' expresion       {
                                            if(!isnan($1) && !isnan($3)){
                                                $$ = $1 + $3;
                                            }else{
                                                $$ = NAN;
                                            }
                                        }
        | expresion '-' expresion       {
                                            if(!isnan($1) && !isnan($3)) {
                                                $$ = $1 - $3;
                                            }else{
                                                $$ = NAN;
                                            }
                                        }
        | expresion '*' expresion       {
                                            if(!isnan($1) && !isnan($3)) {
                                                $$ = $1 * $3;
                                            }else{
                                                $$ = NAN;
                                            }
                                        }
        | expresion '/' expresion       {
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
        | expresion '%' expresion       {   
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
        | expresion '^' expresion       {
                                            if(!isnan($1) && !isnan($3)) {
                                                $$ = pow($1, $3);
                                            }else{
                                                $$ = NAN;
                                            }
                                        }

;

fnc:    FUNC '(' expresion ')'  {
                                    comp = buscarLexema($1);
                                    free($1);
                                    printf("estoy func\n");
                                    $$ = (*(comp.valor.funcptr))($3);
                                }
        | FUNC '(' FICHERO ')'  {   
                                    printf("hola\n");
                                    comp = buscarLexema($1);
                                    free($1);
                                }
;

asig:   VAR '=' expresion       {
                                    if (!error) {
                                        comp = buscarLexema($1);
                                        if (comp.lexema != NULL) {
                                            modificarValorVariable($1, $3);
                                            $$ = $3;
                                            free($1);
                                        } else {
                                            comp.lexema = strdup($1);
                                            comp.valorLexico = VAR;
                                            comp.valor.var = $3;
                                            insertarComponente(comp);
                                            free(comp.lexema);
                                            $$ = $3;
                                            free($1);
                                        }
                                    }
                                }
        
        | CONS  '=' expresion   {
                                    printf(ROJO"Las constantes no se pueden modificar"RESET"\n\n");
                                    error = 1;
                                    $$ = NAN;
                                    free($1);
                                }
;


comando:   CMND0            {
                                comp = buscarLexema($1);
                                free($1);
                                (*(comp.valor.funcptr))();
                            }
        | CMND0 '(' ')'     {
                                comp = buscarLexema($1);
                                free($1);
                                (*(comp.valor.funcptr))();
                            }
;

%%

void yyerror(char *s) {
    printf("SINTAXIS NO VALIDA\n");
}

void cambiarEcho(int valor) {
    doEcho = valor;
    if (doEcho) { 
        printf(VERDE"Echo activado, se imprimirán los resultados."RESET"\n\n");
    }else{
        printf(ROJO"Echo desactivado, no se imrpimiran los resultados."RESET"\n\n");
    }
}

void ejecutandoScript(int valor) {
    script = valor;
    if (!script) {
        printf("\n"AMARILLO"Script ejecutado correctamente."RESET"\n\n"CYAN">"RESET" ");
    }
}