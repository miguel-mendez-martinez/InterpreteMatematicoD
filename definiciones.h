#ifndef DEF_H
#define DEF_H

/**
 * Definiciones de los valores de los componentes lexicosç
 * Sacado de la web de D, los valores van en orden alfabético 
 */
#define ABSTRACT 300
#define ALIAS 301
#define ALIGN 302
#define ASM 303
#define ASSERT 304
#define AUTO 305
#define BOOL 306
#define BREAK 307
#define BYTE 308
#define CASE 309
#define CAST 310
#define CATCH 311
#define CHAR 312
#define CLASS 313
#define CONST 314
#define CONTINUE 315
#define DCHAR 316
#define DEBUG 317
#define DEFAULT 318
#define DELEGATE 319
#define DEPRECATED 320
#define DO 321
#define DOUBLE 322
#define ELSE 323
#define ENUM 324
#define EXPORT 325
#define EXTERN 326
#define FALSE 327
#define FINAL 328
#define FINALLY 329
#define FLOAT 330
#define FOR 331
#define FOREACH 332
#define FOREACH_REVERSE 333
#define FUNCTION 334
#define GOTO 335
#define IF 336
#define IMMUTABLE 337
#define IMPORT 338
#define IN 339
#define INOUT 340
#define INT 341
#define INTERFACE 342
#define INVARIANT 343
#define IS 344
#define LAZY 345
#define LONG 346
#define MACRO 347
#define MIXIN 348
#define MODULE 349
#define NEW 350
#define NOTHROW 351
#define NULLKey 352
#define OUT 353
#define OVERRIDE 354
#define PACKAGE 355
#define PRAGMA 356
#define PRIVATE 357
#define PROTECTED 358
#define PUBLIC 359
#define PURE 360
#define REAL 361
#define REF 362
#define RETURN 363
#define SCOPE 364
#define SHARED 365
#define SHORT 366
#define STATIC 367
#define STRUCT 368
#define SUPER 369
#define SWITCH 370
#define SYNCHRONIZED 371
#define TEMPLATE 372
#define THIS 373
#define THROW 374
#define TRUE 375
#define TRY 376
#define TYPEID 377
#define TYPEOF 378
#define UBYTE 379
#define UINT 380
#define ULONG 381
#define UNION 382
#define UNITTEST 383
#define USHORT 384
#define VERSION 385
#define VOID 386
#define WCHAR 387
#define WHILE 388
#define WITH 389
#define __FILE__Key 390
#define __FILE_FULL_PATH__Key 391
#define __MODULE__Key 392
#define __LINE__Key 393
#define __FUNCTION__Key 394
#define __PRETTY_FUNCTION__Key 395
#define __GSHAREDKey 396
#define __TRAITSKey 397
#define __VECTORKey 398
#define __PARAMETERSKey 399
#define SUMADOBLE 501
#define IGUALDOBLE 502
#define RESTADOBLE 503
#define SUMAIGUAL 504
#define RESTAIGUAL 505
#define DIVIGUAL 506
#define STRING 507
#define MAYORQUE 508
#define MENORQUE 509
#define AMPERDOBLE 510
#define MULTIGUAL 511
#define EXCLAMACIONIGUAL 512
#define MENORIGUAL 513
#define MAYORIGUAL 514

#define ID 500
#define EOFVALUE -100


// Estructura que contiene los lexemas y componentes lexicos
typedef struct  {
    char *identificador;
    int valor;
}tipoelem;

#endif
