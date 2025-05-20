/*---------------Definition des structures principales---------------------*/
SOIT
    BST1 , BST3 , BST2 DES ARB DE (CHAINE);
    Fich UN FICHIER DE (CHAINE) BUFFER S ;
    X , Y , Z DES CARACTERES;
    choix UN ENTIER ;
    QUITTER UN BOOLEEN ;


/*-------------------Declarations des modules----------------------*/
     /*-----input ------*/
    genererFichier UNE ACTION;
    RANDWORD UNE ACTION;

     /*-----construction------*/
    constructBST1  UNE ACTION;
    constructBST3 UNE ACTION;

    insertBST UNE FONCTION (POINTEUR VERS UN ARB DE (CHAINE));
    libererARB UNE ACTION;
    PREORDRE UNE ACTION;

    /*rotation*/
    rotGauche UNE FONCTION (POINTEUR VERS UN ARB DE (CHAINE));
    rotDroite UNE FONCTION (POINTEUR VERS UN ARB DE (CHAINE));
    vers_racine UNE ACTION;

    /*------recherche d'un mot -----------*/
    RECHERECHE UNE ACTION ;
    rechMotBST UNE ACTION;
    rechMotBST1 UNE ACTION;

    /*------test modules--------*/
    INORDRE UNE ACTION;
    HEIGHT UNE FONCTION (ENTIER);
    AFFICH_NIV UNE ACTION;

/*------------------------programme principale----------------------*/
DEBUT
     LIRE(X);
     LIRE(Y);
     LIRE(Z);

     APPEL genererFichier(Fich , X,Y,Z);
     APPEL constructBST1(Fich, BST1 ,X ,Y,Z);
     APPEL constructBST1(Fich, BST3 ,X ,Y,Z);
     /*ADD HERE THE CONSTRUCTION OF BST 2 */

     QUITTER := FAUX;
     TQ ( NON QUITTER )
        ECRIRE('');
	ECRIRE('+---------------------------------------------+');
	ECRIRE('|                    MENU                     |');
	ECRIRE('+---------------------------------------------+');
	ECRIRE('| 1. Parcours Inordre des arbres              |');
	ECRIRE('| 2. Compter les mots commençant par X / Y / Z|');
	ECRIRE('| 3. Compter les mots par niveau              |');
	ECRIRE('| 4. Hauteur des arbres                       |');
	ECRIRE('| 5. Rechercher un mot                        |');
	ECRIRE('| 6. Recherche par intervalle                 |');
	ECRIRE('| 7. Quitter                                  |');
	ECRIRE('+---------------------------------------------+');

        ECRIRE('>> Choisissez une option : ');
        LIRE(choix);
        ECRIRE('');


     FTQ;
       APPEL libererARB(BST1);
       /*APPEL libererARB(BST2);*/
       APPEL libererARB(BST3);
FIN
/*---------------------------MODULES-----------------------------------*/

/*---------CONSTRUCTION-------------------*/
{construction du BST1 a partir du fichier genere}

 ACTION constructBST1(F, TREE , A , B, C)
 SOIT
    F UN FICHIER DE (CHAINES) BUFFER S ;
    TREE UN ARB DE (CHAINE);
    NodesNum UN ENTIER ;
    P , PAR UN POINTEUR VERS UN ARB DE (CHAINE) ;
    STR UNE CHAINE;
    A , B,C DES CARACTERES ;


 DEBUT
   OUVRIR ( F , 'F2.z' , 'A' ) ;
   NodesNum := 0 ;


   TQ NON FINFICH (F )
      LIRESEQ ( F , S ) ;
      P := insertBST(TREE,S );
      SI ( P <> NIL )
         {incrementer le compteur }
         NodesNum := NodesNum + 1 ;

         {si une chaine speciale , deplacer vers la racine }
         STR := struct(INFO(P),1);

         SI (caract(STR,1) = A)OU (caract(STR,1) = B) OU (caract(STR,1) = C)
            APPEL vers_racine(TREE,P);
         FSI;
      FSI;

   FTQ ;

   FERMER ( F);
   ECRIRE ( 'Compte = ' , NodesNum ) ;
 FIN



  ACTION constructBST3(F, TREE , A , B, C)
 SOIT
    F UN FICHIER DE (CHAINES) BUFFER S ;
    TREE UN ARB DE (CHAINE);
    NodesNum UN ENTIER ;
    P , PAR UN POINTEUR VERS UN ARB DE (CHAINE) ;
    STR UNE CHAINE;
    A , B,C DES CARACTERES ;


 DEBUT
   OUVRIR ( F , 'F2.z' , 'A' ) ;
   NodesNum := 0 ;


   TQ NON FINFICH (F )
      LIRESEQ ( F , S ) ;
      P := insertBST(TREE,S );
      SI ( P <> NIL )
         {incrementer le compteur }
         NodesNum := NodesNum + 1 ;

         {si une chaine speciale , deplacer vers la racine }
         STR := struct(INFO(P),1);

         SI (caract(STR,1) <> A) ET (caract(STR,1) <> B) ET (caract(STR,1) <> C)
            APPEL vers_racine(TREE,P);
         FSI;
      FSI;

   FTQ ;

   FERMER ( F);
   ECRIRE ( 'Compte = ' , NodesNum ) ;
 FIN


 /*--------------------------------*/
{inserer un noeud dans le BST}

FONCTION insertBST (TR, STR): POINTEUR VERS UN ARB DE(CHAINE)
SOIT
    N, P ,PAR DES POINTEURS VERS ARB DE (CHAINE);
    TR UN ARB DE (CHAINE);
    STR UNE (CHAINE);
    temp UN ENTIER;

DEBUT

    {rechercher la position d'insertion initiale}
    APPEL rechMotBST(TR,STR,PAR,N , temp);
    {si la chaine n'existe pas deja}

    SI (N = NIL)
       CREERNOEUD (N);
       AFF_INFO(N,STR);
       AFF_PERE(N,PAR);

       SI (TR = NIL)
          TR := N;

       SINON

          SI (struct(STR,1) > struct(INFO(PAR),1))
             AFF_FD(PAR,N);
          SINON
             AFF_FG(PAR,N);
          FSI;
       FSI;

    SINON
       ECRIRE('LA CHAINE EXISTE DEJA');

    FSI;
    insertBST := N;

FIN


/*---------ROTATIONS------------*/
FONCTION rotDroite(P): POINTEUR VERS UN ARB DE(CHAINE)
SOIT
    P, N, B ,PAR DES POINTEUR VERS UN ARB DE (CHAINE);
DEBUT
    SI (P = NIL) OU (FG(P) = NIL)
       rotDroite := P;
    SINON
       PAR := PERE(P);

       N := FG(P);
       B := FD(N);
       AFF_FD(N, P);
       AFF_PERE(P, N);
       AFF_FG(P, B);
       SI (B <> NIL)
          AFF_PERE(B, P);
       FSI;
       AFF_PERE(N,PAR);
       SI ( PAR <> NIL )
          SI ( P = FG (PAR))
             AFF_FG(PAR,N);
          SINON
             AFF_FD(PAR,N);
          FSI;
       FSI;
       rotDroite := N;
    FSI;
FIN


FONCTION rotGauche (P): POINTEUR VERS UN ARB DE(CHAINE)
SOIT
    P , N , B ,PAR DES POINTEUR VERS UN ARB DE (CHAINE);

DEBUT
    SI (P = NIL) OU (FD(P) = NIL)
       rotGauche := P;
    SINON
       PAR := PERE(P);
       N := FD(P);

       B := FG(N);
       AFF_FG(N, P);
       AFF_PERE(P, N);
       AFF_FD(P, B);

       SI (B <> NIL)
          AFF_PERE(B, P);
       FSI;

       AFF_PERE(N,PAR);
       SI ( PAR <> NIL )
          SI ( P = FG (PAR))
             AFF_FG(PAR,N);
          SINON
             AFF_FD(PAR,N);
          FSI;
       FSI;
       rotGauche := N;
    FSI;
FIN

ACTION vers_racine(R, P)
SOIT
    R UN ARB DE (CHAINE);
    P, PAR, N DES POINTEURS VERS UN ARB DE (CHAINE);
DEBUT

    SI (P <> NIL)
       PAR := PERE(P);
       TQ (PAR <> NIL)
          SI (FG(PAR) = P)
            P := rotDroite(PAR);
          SINON
             P := rotGauche(PAR);
          FSI;
          PAR := PERE(P);
       FTQ;
    FSI;
    R := P ;
FIN


/*--------------MODULES DU TEST ------------------------------*/
ACTION INORDRE(TR)
SOIT
    TR ,P , Q DES ARB DE (CHAINE);
    NOTEMPTY UN BOOLEEN ;
    Pil UNE PILE DE ARB DE (CHAINE);
DEBUT
    CREERPILE ( Pil ) ;
    P := TR ;
    NOTEMPTY := VRAI ;

    TQ NOTEMPTY :
      TQ P <> NIL :
         EMPILER ( Pil , P ) ;
         P := FG ( P )
         FTQ ;

      SI NON PILEVIDE ( Pil ) :
         DEPILER ( Pil , P ) ;
         ECRIRE(INFO(P));
         P := FD ( P ) ;

      SINON
         NOTEMPTY := FAUX
      FSI

    FTQ
FIN

/*-----------------------------------*/
FONCTION HEIGHT(TR): ENTIER
SOIT
    TR UN ARB DE (CHAINE);

DEBUT
    SI ( TR = NIL )
       HEIGHT := -1 ;
    SINON SI (FG(TR) = NIL ) ET (FD(TR) = NIL )
       HEIGHT := 0 ;
          SINON
            HEIGHT := MAX(HEIGHT(FG(TR)),HEIGHT(FD(TR))) + 1 ;
          FSI;
    FSI;
FIN
/*----------------------------------------*/
ACTION AFFICH_NIV(R,A,B,C)
SOIT
    R , P DES ARB DE (CHAINE);
    A , B, C DES CARACTERES;
    F1 UNE FILE DE ARB DE (CHAINE);
    F2 UNE FILE DE ENTIER ;
    NIV UN ENTIER;
    STR UNE CHAINE;
DEBUT
     SI ( R <> NIL )
        CREERFILE(F1);
        CREERFILE(F2); {pour garder le niveau de chaque noeud enfile}

        {enfile la racine et son niveau}
        ENFILER(F1,R);
        NIV := 0 ;
        ENFILER(F2,NIV);

        TQ ( NON FILEVIDE (F1) ) ET ( NON FILEVIDE (F2) )
           DEFILER(F1,P);
           DEFILER (F2, NIV);

            /*PROCESS*/
            STR := STRUCT(INFO(P),1);
           SI ( CARACT(STR,1) = A) OU ( CARACT(STR,1) = B) OU ( CARACT(STR,1) = C)
              ECRIRE(STR,'NIVEAU:',NIV);
           FSI;

           SI(FG(P) <> NIL)
              ENFILER(F1,FG(P));
              ENFILER(F2, NIV+1 );
           FSI;

           SI(FD(P) <> NIL)
              ENFILER(F1,FD(P));
              ENFILER(F2, NIV+1 );
           FSI;
        FTQ;

     FSI;
FIN

/*---------------------------SEARCH---------------------*/

/*----------WORD SEARCH---------*/
 {recherecher une chaine a l'aide du triplet ( bst1,2,3)}

 ACTION RECHERECHE( STR , PAR , P , PATH , X, Y ,Z)
 SOIT
     STR , TEMP DES CHAINES;
     PAR , P DES POINTEURS VERS UN ARB DE (CHAINE) ;
     PATH UN ENTIER ;
     X , Y , Z DES CARACTERES;
 DEBUT
      PATH := 0 ;
      SI ( caract(STR , 1) = X ) OU ( caract(STR , 1) = X ) OU ( caract(STR , 1) = X )
         APPEL rechMotBST1(BST1 , STR , PAR , P ,X , Y , Z );

      SINON SI (caract(STR, 1) > X) OU (caract(STR, 1) > Y) OU (caract(STR, 1) > Z)
               APPEL rechMotBST(BST2 , STR , PAR , P );
            SINON
               APPEL rechMotBST(BST3 , STR , PAR , P );
            FSI;
      FSI;
 FIN

 /*----------------------------------------*/
{Rechercher une chaine STR dans un BST TR}
 ACTION rechMotBST(TR , STR , PAR , P , PATH )
 SOIT
     TR UN ARB DE (CHAINE);
     PAR , P DES POINTEURS VERS ARB DE (CHAINE);
     STR UNE (CHAINE);
     TROUVE UN BOOLEEN;
     PATH UN ENTIER ;

 DEBUT
      PAR := NIL ;

      SI ( TR = NIL )
         P := NIL ;
         PATH := 0 ;

      SINON
         P := TR;
         PATH := 1;
         TROUVE := FAUX ;
         TANTQUE  (P <> NIL) ET  (NON TROUVE)
               SI ( struct(INFO(P),1) = struct(STR,1) )
                  TROUVE := VRAI;
               SINON
                     PATH := PATH + 1 ;
                     PAR := P ;
                     SI struct(STR,1) < struct(INFO ( P ),1)
                        P := FG ( PAR ) ;

                     SINON
                        P := FD ( PAR ) ;

                     FSI ;
              FSI;
         FTQ;

      FSI;
 FIN
 /*---------------------------------------*/
 ACTION rechMotBST1(TR , STR , PAR , P , PATH ,X , Y , Z )
 SOIT
     TR UN ARB DE (CHAINE);
     PAR , P DES POINTEURS VERS ARB DE (CHAINE);
     temp UNE CHAINE;
     STR UNE (CHAINE);
     TROUVE UN BOOLEEN;
     X , Y , Z DES CARACTERES;
     PATH UN ENTIER ;

 DEBUT
      PAR := NIL ;

      SI ( TR = NIL )
         P := NIL ;
         PATH := 0 ;

      SINON
         P := TR;
         PATH := 1;
         TROUVE := FAUX ;

         TANTQUE  (P <> NIL) ET  (NON TROUVE)
               SI ( struct(INFO(P),1) = struct(STR,1) )
                  TROUVE := VRAI;

               /*arret au premier mot non-special*/
               SINON
                    temp := struct(INFO(P),1) ;
                    SI (caract(temp,1) <> X) ET (caract(temp,1) <> Y) ET (caract(temp,1) <> Z)
                       P := NIL ;
                    SINON
                         PAR := P ;
                         PATH := PATH + 1 ;
                         SI struct(STR,1) < struct(INFO ( P ),1)
                         P := FG ( PAR ) ;

                         SINON
                         P := FD ( PAR ) ;

                         FSI ;
                    FSI;
               FSI;
         FTQ;

      FSI;
 FIN

/*-----generer le fichier ------*/
ACTION  genererFichier(F , A,B,C)
 SOIT
      F UN FICHIER DE (CHAINES) BUFFER S ;
      J, I : ENTIER ;
       WORD UNE CHAINE;
       A , B , C DES CARACTERES;

 DEBUT

      OUVRIR(F,'F2.z','N');
      POUR J:= 1, 101
          APPEL RANDWORD(WORD, I, A, B, C);
          init_struct(S, [WORD]);
          ECRIRESEQ ( F , S )
      FPOUR ;
      FERMER ( F);

 FIN

{genere des mots aleatoires}
 ACTION RANDWORD(WORD, I, A, B, C)
    SOIT
       I : ENTIER ;
       WORD UNE CHAINE;
       A , B , C DES CHAINES;
    DEBUT
       I := ALEANOMBRE(10);
       SI I = 0
          WORD := A + ALEACHAINE(ALEANOMBRE(5) + 3);
       SINON SI I = 1
             WORD := B + ALEACHAINE(ALEANOMBRE(5) + 3);
             SINON SI I = 2
                    WORD := C + ALEACHAINE(ALEANOMBRE(5) + 3);

                    SINON WORD := ALEACHAINE(ALEANOMBRE(5) + 3);
                    FSI;
             FSI;
      FSI;
 FIN


ACTION libererARB(R)
SOIT
    R UN ARB DE (CHAINE);
    TempGauche, TempDroit DES POINTEURS VERS UN ARB DE (CHAINE);
DEBUT
    SI (R <> NIL)
       TempGauche := FG(R);
       TempDroit := FD(R);
       APPEL libererARB(TempGauche);
       APPEL libererARB(TempDroit);
       LIBERERNOEUD(R);
    FSI;
FIN


ACTION PREORDRE(R)
SOIT
    R UN ARB DE (CHAINE);
DEBUT
   SI(R<>NIL)
     ECRIRE(INFO(R));
     APPEL PREORDRE(FG(R));
     APPEL PREORDRE(FD(R));
   FSI;
FIN
