%{
#include <math.h>

#include "lex.yy.h"
#include "tablaSimbolos.h"

CompLexico comp;
/*Flags para el interprete, de manera que sepa que hacer*/
int doEcho = 1;
int script = 0;
int error = =;

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
%token <cadena> CONST VAR FUNC CMND0 CMND1 FICHEIRO LIB

%type <numero> exp asig cmnd fnc

%left '-' '+'
%left '*' '/'
%left '%'
%precedence NEG
%right '^'

%%

entrada: %empty         {
                            if(!script){
                                print(CYAN">"RESET" ");
                            }
                        }
        | entrada linea
;

linea:  '\n'                { print(CYAN">"RESET" "); }
       | exp '\n'           {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | exp ';' '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | asig '\n'           {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | asig ';' '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | cmnd '\n'         {
                                if(isnan($1) && !error){
                                    printf("NAN DETECTADO");
                                }
                                if(!script){
                                    print(CYAN">"RESET" ");
                                }
                                error = 1;
                            }
        | cmnd ';' '\n'     {
                                if(isnan($1) && !error){
                                    printf("NAN DETECTADO");
                                }
                                if(!script){
                                    print(CYAN">"RESET" ");
                                }
                                error = 1;
                            }
        | fnc '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
        | fnc ';' '\n'      {
                                if (!error) {
                                    if(isnan($1)){
                                        printf("NAN DETECTADO");
                                    }else if(doEcho){
                                        printf(VERDE"%lf"RESET"\n\n", $1);
                                    }
                                }
                                if (!script) {
                                    print(CYAN">"RESET" ");
                                }
                                error = 0;
                            }
;


%%


C ́odigo C adicional