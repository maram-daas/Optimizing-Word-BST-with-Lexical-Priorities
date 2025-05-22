  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             RÃ©alisÃ©e par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  /*---------------Definition des structures principales---------------------*/


  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  typedef int bool ;
  typedef char * string255 ;
  typedef char * string2 ;

  #define True 1
  #define False 0

  void clear_screen() {
    system("cls");
}


  /** ImplÃ©mentation **\: ARBRE BINAIRE DE STRUCTURES**/

  /** Structures statiques **/

  typedef struct Ts Type_Ts  ;
  typedef Type_Ts * Typestr_Ts ;
  typedef string255 Type1_Ts  ;
  struct Ts
    {
      Type1_Ts Champ1 ;
    };

  Type1_Ts Struct1_Ts ( Typestr_Ts S)
    {
      return  S->Champ1 ;
    }

  void Aff_struct1_Ts ( Typestr_Ts S, Type1_Ts Val )
    {
      strcpy( S->Champ1 , Val );
    }


  /** Arbres de recherche binaire **/

  typedef Typestr_Ts Typeelem_ATs   ;
  typedef struct Noeud_ATs * Pointeur_ATs ;

  struct Noeud_ATs
    {
      Typeelem_ATs  Val ;
      Pointeur_ATs Fg ;
      Pointeur_ATs Fd ;
      Pointeur_ATs Pere ;
     } ;

  Typeelem_ATs Info_ATs( Pointeur_ATs P )
    { return P->Val;   }

  Pointeur_ATs Fg_ATs( Pointeur_ATs P)
    { return P->Fg ; }

  Pointeur_ATs Fd_ATs( Pointeur_ATs P)
    { return P->Fd ; }

  Pointeur_ATs Pere_ATs( Pointeur_ATs P)
    { return P->Pere ; }

  void Aff_info_ATs ( Pointeur_ATs P, Typeelem_ATs Val)
    {
      Typeelem_ATs _Temp ;
      _Temp = malloc(sizeof(Type_Ts));
      _Temp->Champ1 = malloc(255 * sizeof(char));
      /* Affectation globale de structure */
      strcpy(_Temp->Champ1, Val->Champ1);
      Val = _Temp ;
       P->Val = Val ;
    }

  void Aff_fg_ATs( Pointeur_ATs P, Pointeur_ATs Q)
    { P->Fg =  Q;  }

  void Aff_fd_ATs( Pointeur_ATs P, Pointeur_ATs Q)
    { P->Fd =  Q ; }

  void Aff_pere_ATs( Pointeur_ATs P, Pointeur_ATs Q)
    { P->Pere =  Q ; }

  void Creernoeud_ATs( Pointeur_ATs *P)
    {
      *P = (struct Noeud_ATs *) malloc( sizeof( struct Noeud_ATs))   ;
      (*P)->Val = malloc(sizeof(Type_Ts));
      (*P)->Val->Champ1 = malloc( 255 * sizeof(char));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_ATs( Pointeur_ATs P)
    { free( P ) ; }


  /** ImplÃ©mentation **\: FICHIER
  /* Traitement des fichiers ouverts */

  /* Traitement des fichiers ouverts */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Pile_ouverts  = NULL;

  /* Teste si un fichier est ouvert */
  _Ptr_Noeud _Ouvert ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Pile_ouverts; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Ajouter un fichier ouvert */
  void _Empiler_ouvert ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Pile_ouverts;
      _Pile_ouverts = P;
    }

  /* Supprimer un fichier ouvert et rendre son nom*/
  char * _Depiler_ouvert ( FILE *Fl)
    {
      char * Fp = malloc (100);
      _Ptr_Noeud P,  Prec  ;
      P= _Pile_ouverts;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Pile_ouverts = P->Suiv;
      free (P);
      return Fp ;
    }


  /** Fichiers **/

  typedef char _Tx[255];
  /** Types des champs du bloc **/
  typedef string255 Typechamp1_s;
  typedef _Tx Typechamp1_s_Buf ;

  /** Type du bloc de données du fichier **/
  typedef struct
    {
      Typechamp1_s_Buf Champ1 ;
    }  Typestruct1_s_Buf;

  /** Type de la structure du bloc de données du fichier **/
  typedef struct
    {
      Typechamp1_s Champ1 ;
    }  Typestruct1_s_;

  typedef Typestruct1_s_  * Typestruct1_s ;


  /** Machine abstaite sur les fichiers **/

  void Ouvrir_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Ouvert(Fp);
      if ( P != NULL )
      /* Le fichier est déjà ouvert */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* Le fichier est non ouvert */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      _Empiler_ouvert( Fp, *s);
    }

  void Fermer_s ( FILE * s )
    {
      char * Fp = malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, _Depiler_ouvert(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le même nom ?  */
      /* Si Oui, le Réouvrir à la position sauvegardée */
      P =  _Ouvert (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Ecrireseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Ecriredir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Lireseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer.Champ1); ++J)
        Buf->Champ1[J] = Buffer.Champ1[J];
      }
    }

  void Liredir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer.Champ1); ++J)
        Buf->Champ1[J] = Buffer.Champ1[J];
    }

  void Rajouter_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fseek(s, 0, 2); /* Fin du fichier */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Finfich_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* Fin du fichier */
      long K2 = ftell(s);   /* position à partir du debut */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_bloc_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* Fin du fichier */
      K = ftell(s);   /* position à partir du debut */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }


  /** ImplÃ©mentation **\: PILE DE ARBRES BINAIRES DE STRUCTURES**/
  /** Piles **/

  typedef Pointeur_ATs Typeelem_PATs ;
  typedef struct Maillon_PATs * Pointeur_PATs ;
  typedef   Pointeur_PATs  Typepile_PATs  ;

  struct Maillon_PATs
    {
      Typeelem_PATs  Val ;
      Pointeur_PATs Suiv ;
    } ;

  void Creerpile_PATs( Pointeur_PATs *P )
    { *P = NULL ; }

  bool Pilevide_PATs ( Pointeur_PATs P )
    { return  (P == NULL ); }

  void Empiler_PATs ( Pointeur_PATs *P,  Typeelem_PATs Val )
    {
      Pointeur_PATs Q;

      Q = (struct Maillon_PATs *) malloc( sizeof( struct Maillon_PATs))   ;
      Q->Val = Val ;
      Q->Suiv = *P;
      *P = Q;
    }

  void Depiler_PATs ( Pointeur_PATs *P,  Typeelem_PATs *Val )
    {
      Pointeur_PATs Sauv;

      if (! Pilevide_PATs (*P) )
        {
          *Val = (*P)->Val ;
          Sauv = *P;
          *P = (*P)->Suiv;
          free(Sauv);
        }
      else printf ("%s \n", "Pile vide");
    }


  /** ImplÃ©mentation **\: FILE DE ARBRES BINAIRES DE STRUCTURES**/
  /** Files d'attente **/

  typedef Pointeur_ATs Typeelem_FATs ;
  typedef  struct Filedattente_FATs * Pointeur_FATs ;
  typedef  struct Maillon_FATs * Ptliste_FATs ;

  struct Maillon_FATs
    {
      Typeelem_FATs Val ;
      Ptliste_FATs Suiv  ;
    };

  struct Filedattente_FATs
    {
      Ptliste_FATs Tete, Queue ;
    };

  void Creerfile_FATs ( Pointeur_FATs *Fil   )
    {
      *Fil = (struct Filedattente_FATs *) malloc( sizeof( struct Filedattente_FATs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_FATs (Pointeur_FATs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_FATs ( Pointeur_FATs Fil , Typeelem_FATs Val   )
    {
      Ptliste_FATs Q;

      Q = (struct Maillon_FATs *) malloc( sizeof( struct Maillon_FATs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_FATs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_FATs (Pointeur_FATs Fil, Typeelem_FATs *Val )
    {
      if (! Filevide_FATs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }


  /** ImplÃ©mentation **\: FILE DE ENTIERS**/
  /** Files d'attente **/

  typedef int Typeelem_Fi ;
  typedef  struct Filedattente_Fi * Pointeur_Fi ;
  typedef  struct Maillon_Fi * Ptliste_Fi ;

  struct Maillon_Fi
    {
      Typeelem_Fi Val ;
      Ptliste_Fi Suiv  ;
    };

  struct Filedattente_Fi
    {
      Ptliste_Fi Tete, Queue ;
    };

  void Creerfile_Fi ( Pointeur_Fi *Fil   )
    {
      *Fil = (struct Filedattente_Fi *) malloc( sizeof( struct Filedattente_Fi)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_Fi (Pointeur_Fi Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_Fi ( Pointeur_Fi Fil , Typeelem_Fi Val   )
    {
      Ptliste_Fi Q;

      Q = (struct Maillon_Fi *) malloc( sizeof( struct Maillon_Fi))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_Fi(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_Fi (Pointeur_Fi Fil, Typeelem_Fi *Val )
    {
      if (! Filevide_Fi(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }


  /** ImplÃ©mentation **\: TABLEAU DE ENTIERS**/

  /** Tableaux **/

  typedef int Typeelem_V50i ;
  typedef Typeelem_V50i * Typevect_V50i ;

  Typeelem_V50i Element_V50i ( Typevect_V50i V , int I1  )
    {
      return  *(V +  (I1-1)  ) ;
    }

  void Aff_element_V50i ( Typevect_V50i V  , int I1 ,  Typeelem_V50i Val )
    {
      *(V +  (I1-1)  ) = Val ;
    }

  /** Variables du programme principal **/
  Pointeur_ATs Bst1=NULL;
  Pointeur_ATs Bst3=NULL;
  Pointeur_ATs Bst2=NULL;
  FILE *Fich;
  Typestruct1_s S ;
  string2 X;
  string2 Y;
  string2 Z;
  int Choix;
  int Num;
  bool Quitter;

  /** Fonctions standards **/

  char *Caract ( string255 Ch , int I )
    {
      char *s = malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }


  /** Initialisation d'une structure **/
  void Init_struct_Ts ( Typestr_Ts S, Type_Ts S_ )
    {
      S->Champ1 = S_.Champ1 ;
    }


  /** Prototypes des fonctions **/

  void Constructbst2 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  void Vers_milieu (Pointeur_ATs *R , Pointeur_ATs *P);
  void Rangequery (Pointeur_ATs *Tr , string2 *A , string2 *B , string2 *C);
  void Constructbst1 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  void Constructbst3 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  Pointeur_ATs Insertbst (Pointeur_ATs *Tr , Typestr_Ts *Str) ;
  Pointeur_ATs Rotdroite (Pointeur_ATs *P) ;
  Pointeur_ATs Rotgauche (Pointeur_ATs *P) ;
  void Vers_racine (Pointeur_ATs *R , Pointeur_ATs *P);
  void Inordre (Pointeur_ATs *Tr);
  int  Height (Pointeur_ATs *Tr) ;
  void Affich_niv (Pointeur_ATs *R , string2 *A , string2 *B , string2 *C);
  void Comptespecial (Pointeur_ATs *R , string2 *X , string2 *Y , string2 *Z , int *Count);
  void Rechereche (string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z);
  void Rechmotbst (Pointeur_ATs *Tr , Typestr_Ts *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path);
  void Rechmotbst1 (Pointeur_ATs *Tr , Typestr_Ts *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z);
  void Genererfichier (FILE *F , string2 *A , string2 *B , string2 *C);
  void Randword (string255 *Word , int *I , string255 *A , string255 *B , string255 *C);
  void Libererarb (Pointeur_ATs *R);
  void Preordre (Pointeur_ATs *R);

  /*---------------------------MODULES-----------------------------------*/
  /*---------CONSTRUCTION-------------------*/
  void Constructbst2 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       P  =  Insertbst ( & *Tree , & S ) ;
      /*incrementer le compteur */
       if( ( P != NULL )) {
         Nodesnum  =  Nodesnum + 1 ;
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) == 0  ) || (strcmp( Caract ( Str , 1 ), *B) == 0  ) || (strcmp( Caract ( Str , 1 ), *C) == 0  )) {
           Vers_milieu ( & *Tree , & P ) ;

         } ;

       } ;

 } ;
     Fermer_s ( F ) ;
     printf ( " %s", "Compte = " );
     printf ( " %d", Nodesnum ) ;

    }
  void Vers_milieu (Pointeur_ATs *R , Pointeur_ATs *P)
    {
      /** Variables locales **/
      Pointeur_ATs Par=NULL;
      Pointeur_ATs N=NULL;
      int L;
      int Cpt;

      /** Corps du module **/
     Cpt  =  0 ;
     if( ( *P != NULL )) {
       Par  =  Pere_ATs ( *P ) ;
       L  =  Height ( & *R ) ;
       L  =  L / 2 ;
       while( ( Par != NULL ) && ( Cpt < L )) {
         if( ( Fg_ATs ( Par ) == *P )) {
           *P  =  Rotdroite ( & Par ) ;
           }
         else
           {
           *P  =  Rotgauche ( & Par ) ;

         } ;
         Par  =  Pere_ATs ( *P ) ;
         Cpt  =  Cpt + 1 ;

 } ;

     } ;
     if( Pere_ATs ( *P ) == NULL) {
       *R  =  *P ;

     }
    }
  void Rangequery (Pointeur_ATs *Tr , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Pointeur_ATs P=NULL;
      Pointeur_ATs Q=NULL;
      bool Notempty;
      Pointeur_PATs Pil=NULL;
      string255 Str;
      int Cpt;
      string255 Word;
      int I;
      string255 Maxi;
      string255 Mini;
      Type_Ts _Struct_Temp1;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     Word = malloc(255 * sizeof(char));
     Maxi = malloc(255 * sizeof(char));
     Mini = malloc(255 * sizeof(char));
     Creerpile_PATs (& Pil ) ;
     P  =  *Tr ;
     Notempty  =  True ;
     Randword ( & Mini , & I , & *A , & *B , & *C ) ;
     Randword ( & Maxi , & I , & *A , & *B , & *C ) ;
     printf ( " %s", "MIN WORD: " ) ;
     printf ( " %s", Mini ) ;
     printf ( " %s", "MAX WORD: " ) ;
     printf ( " %s", Maxi ) ;
     Cpt  =  0 ;
     while( Notempty)  {
       while( P != NULL)  {
         Empiler_PATs (& Pil , P ) ;
         P  =  Fg_ATs ( P );
 } ;
       if( ! Pilevide_PATs ( Pil ))   {
         Depiler_PATs (& Pil , &P ) ;
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if(strcmp( Caract ( Str , 1 ), Caract ( Maxi , 1 )) < 0 )   {
           if(strcmp( Caract ( Str , 1 ), Caract ( Mini , 1 )) > 0 )   {
             /** Ecriture d'une structure */
             _Struct_Temp1 = *Info_ATs(P);
             printf ( " %s", _Struct_Temp1.Champ1 ) ;
             Cpt  =  Cpt + 1 ;

           }
         } ;
         P  =  Fd_ATs ( P ) ;
         }
       else
         {
         Notempty  =  False;
       }
 } ;
     printf ( " %s", "NUMBER OF WORDS FOUND :" ) ;
     printf ( " %d", Cpt ) ;

    }
  /*construction du BST1 a partir du fichier genere*/
  void Constructbst1 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       P  =  Insertbst ( & *Tree , & S ) ;
      /*incrementer le compteur */
       if( ( P != NULL )) {
         Nodesnum  =  Nodesnum + 1 ;
        /*si une chaine speciale , deplacer vers la racine */
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) == 0  ) || (strcmp( Caract ( Str , 1 ), *B) == 0  ) || (strcmp( Caract ( Str , 1 ), *C) == 0  )) {
           Vers_racine ( & *Tree , & P ) ;

         } ;

       } ;

 } ;
     Fermer_s ( F ) ;
     printf ( " %s", "Compte = " );
     printf ( " %d", Nodesnum ) ;

    }
  void Constructbst3 (FILE *F , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       P  =  Insertbst ( & *Tree , & S ) ;
      /*incrementer le compteur */
       if( ( P != NULL )) {
         Nodesnum  =  Nodesnum + 1 ;
        /*si une chaine speciale , deplacer vers la racine */
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) != 0  ) && (strcmp( Caract ( Str , 1 ), *B) != 0  ) && (strcmp( Caract ( Str , 1 ), *C) != 0  )) {
           Vers_racine ( & *Tree , & P ) ;

         } ;

       } ;

 } ;
     Fermer_s ( F ) ;
     printf ( " %s", "Compte = " );
     printf ( " %d", Nodesnum ) ;

    }
  /*--------------------------------*/
  /*inserer un noeud dans le BST*/
  Pointeur_ATs Insertbst (Pointeur_ATs *Tr , Typestr_Ts *Str)
    {
      /** Variables locales **/
      Pointeur_ATs Insertbst2 =NULL;
      Pointeur_ATs N=NULL;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      int Temp;

      /** Corps du module **/
     Rechmotbst ( & *Tr , & *Str , & Par , & N , & Temp ) ;
    /*si la chaine n'existe pas deja*/
     if( ( N == NULL )) {
       Creernoeud_ATs (& N ) ;
       Aff_info_ATs ( N , *Str ) ;
       Aff_pere_ATs ( N , Par ) ;
       if( ( *Tr == NULL )) {
         *Tr  =  N ;
         }
       else
         {
         if( (strcmp( Struct1_Ts ( *Str  ), Struct1_Ts ( Info_ATs ( Par )  )) > 0  )) {
           Aff_fd_ATs ( Par , N ) ;
           }
         else
           {
           Aff_fg_ATs ( Par , N ) ;

         } ;

       } ;
       }
     else
       {
       printf ( " %s", "LA CHAINE EXISTE DEJA" ) ;

     } ;
     Insertbst2  =  N ;

     return Insertbst2 ;
    }
  /*---------ROTATIONS------------*/
  Pointeur_ATs Rotdroite (Pointeur_ATs *P)
    {
      /** Variables locales **/
      Pointeur_ATs Rotdroite2 =NULL;
      Pointeur_ATs N=NULL;
      Pointeur_ATs B=NULL;
      Pointeur_ATs Par=NULL;

      /** Corps du module **/
     if( ( *P == NULL ) || ( Fg_ATs ( *P ) == NULL )) {
       Rotdroite2  =  *P ;
       }
     else
       {
       Par  =  Pere_ATs ( *P ) ;
       N  =  Fg_ATs ( *P ) ;
       B  =  Fd_ATs ( N ) ;
       Aff_fd_ATs ( N , *P ) ;
       Aff_pere_ATs ( *P , N ) ;
       Aff_fg_ATs ( *P , B ) ;
       if( ( B != NULL )) {
         Aff_pere_ATs ( B , *P ) ;

       } ;
       Aff_pere_ATs ( N , Par ) ;
       if( ( Par != NULL )) {
         if( ( *P == Fg_ATs ( Par ) )) {
           Aff_fg_ATs ( Par , N ) ;
           }
         else
           {
           Aff_fd_ATs ( Par , N ) ;

         } ;

       } ;
       Rotdroite2  =  N ;

     } ;

     return Rotdroite2 ;
    }
  Pointeur_ATs Rotgauche (Pointeur_ATs *P)
    {
      /** Variables locales **/
      Pointeur_ATs Rotgauche2 =NULL;
      Pointeur_ATs N=NULL;
      Pointeur_ATs B=NULL;
      Pointeur_ATs Par=NULL;

      /** Corps du module **/
     if( ( *P == NULL ) || ( Fd_ATs ( *P ) == NULL )) {
       Rotgauche2  =  *P ;
       }
     else
       {
       Par  =  Pere_ATs ( *P ) ;
       N  =  Fd_ATs ( *P ) ;
       B  =  Fg_ATs ( N ) ;
       Aff_fg_ATs ( N , *P ) ;
       Aff_pere_ATs ( *P , N ) ;
       Aff_fd_ATs ( *P , B ) ;
       if( ( B != NULL )) {
         Aff_pere_ATs ( B , *P ) ;

       } ;
       Aff_pere_ATs ( N , Par ) ;
       if( ( Par != NULL )) {
         if( ( *P == Fg_ATs ( Par ) )) {
           Aff_fg_ATs ( Par , N ) ;
           }
         else
           {
           Aff_fd_ATs ( Par , N ) ;

         } ;

       } ;
       Rotgauche2  =  N ;

     } ;

     return Rotgauche2 ;
    }
  void Vers_racine (Pointeur_ATs *R , Pointeur_ATs *P)
    {
      /** Variables locales **/
      Pointeur_ATs Par=NULL;
      Pointeur_ATs N=NULL;

      /** Corps du module **/
     if( ( *P != NULL )) {
       Par  =  Pere_ATs ( *P ) ;
       while( ( Par != NULL )) {
         if( ( Fg_ATs ( Par ) == *P )) {
           *P  =  Rotdroite ( & Par ) ;
           }
         else
           {
           *P  =  Rotgauche ( & Par ) ;

         } ;
         Par  =  Pere_ATs ( *P ) ;

 } ;

     } ;
     *R  =  *P ;

    }
  /*--------------MODULES DU TEST ------------------------------*/
  void Inordre (Pointeur_ATs *Tr)
    {
      /** Variables locales **/
      Pointeur_ATs P=NULL;
      Pointeur_ATs Q=NULL;
      bool Notempty;
      Pointeur_PATs Pil=NULL;
      Type_Ts _Struct_Temp2;

      /** Corps du module **/
     Creerpile_PATs (& Pil ) ;
     P  =  *Tr ;
     Notempty  =  True ;
     while( Notempty)  {
       while( P != NULL)  {
         Empiler_PATs (& Pil , P ) ;
         P  =  Fg_ATs ( P );
 } ;
       if( ! Pilevide_PATs ( Pil ))   {
         Depiler_PATs (& Pil , &P ) ;
         /** Ecriture d'une structure */
         _Struct_Temp2 = *Info_ATs(P);
         printf ( " %s", _Struct_Temp2.Champ1 ) ;
         P  =  Fd_ATs ( P ) ;
         }
       else
         {
         Notempty  =  False;
       }
 }
    }
  /*-----------------------------------*/
  int  Height (Pointeur_ATs *Tr)
    {
      /** Variables locales **/
      int  Height2 ;
      Pointeur_ATs _Px1=NULL;
      Pointeur_ATs _Px2=NULL;

      /** Corps du module **/
     if( ( *Tr == NULL )) {
       Height2  =  - 1 ;
       }
     else
       {
       if( ( Fg_ATs ( *Tr ) == NULL ) && ( Fd_ATs ( *Tr ) == NULL )) {
         Height2  =  0 ;
         }
       else
         {
         _Px1 =  Fg_ATs ( *Tr ) ;
         _Px2 =  Fd_ATs ( *Tr ) ;
         Height2  =  Max ( Height ( &_Px1) , Height ( &_Px2) ) + 1 ;

       } ;

     } ;

     return Height2 ;
    }
  /*----------------------------------------*/
  void Affich_niv (Pointeur_ATs *R , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Pointeur_ATs P=NULL;
      Pointeur_FATs F1=NULL;
      Pointeur_Fi F2=NULL;
      int Niv;
      int N;
      int I;
      string255 Str;
      Typevect_V50i T;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     T = malloc(50 * sizeof(int));
     if( ( *R != NULL )) {
       Creerfile_FATs (& F1 ) ;
       Creerfile_Fi (& F2 ) ;
       N  =  Height ( & *R ) + 1 ;
      /*la hauteur du l'arb = taille du tab*/
      /* Initialiser le tableau T Ã  0 */
       for( I  =  1 ;I <=  50 ; ++I) {
         Aff_element_V50i ( T , I   , 0 ) ;

       } ;
      /* Enfiler la racine*/
       Enfiler_FATs ( F1 , *R ) ;
       Niv  =  0 ;
       Enfiler_Fi ( F2 , Niv ) ;
       while( ( ! Filevide_FATs ( F1 ) ) && ( ! Filevide_Fi ( F2 ) )) {
         Defiler_FATs ( F1 , &P ) ;
         Defiler_Fi ( F2 , &Niv ) ;
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
        /* traiter le nÅ“ud courant  */
         if( (strcmp( Caract ( Str , 1 ), *A) == 0  ) || (strcmp( Caract ( Str , 1 ), *B) == 0  ) || (strcmp( Caract ( Str , 1 ), *C) == 0  )) {
           Aff_element_V50i ( T , Niv + 1   , Element_V50i ( T , Niv + 1   ) + 1 ) ;
           printf ( " %s", "ELEMENT:" );
           printf ( " %s", Str );
           printf ( " %s", "NIVEAU" );
           printf ( " %d", Niv ) ;

         } ;
         if( ( Fg_ATs ( P ) != NULL )) {
           Enfiler_FATs ( F1 , Fg_ATs ( P ) ) ;
           Enfiler_Fi ( F2 , Niv + 1 ) ;

         } ;
         if( ( Fd_ATs ( P ) != NULL )) {
           Enfiler_FATs ( F1 , Fd_ATs ( P ) ) ;
           Enfiler_Fi ( F2 , Niv + 1 ) ;

         } ;

 } ;
      /*AFFICHAGE*/
       for( I  =  1 ;I <=  N ; ++I){
         printf ( " %s", "NIVEAU" );
         printf ( " %d", I );
         printf ( " %s", "NOMBRE" );
         printf ( " %d", Element_V50i(T,I) ) ;

       } ;

     } ;

    }
  /*------------------------------------------------------------------------------------*/
  void Comptespecial (Pointeur_ATs *R , string2 *X , string2 *Y , string2 *Z , int *Count)
    {
      /** Variables locales **/
      string255 Temp;
      Pointeur_ATs _Px1=NULL;
      Pointeur_ATs _Px2=NULL;

      /** Corps du module **/
     Temp = malloc(255 * sizeof(char));
     if( ( *R != NULL )) {
       strcpy (Temp,   Struct1_Ts ( Info_ATs ( *R )  )) ;
       if( (strcmp( Caract ( Temp , 1 ), *X) == 0  ) || (strcmp( Caract ( Temp , 1 ), *Y) == 0  ) || (strcmp( Caract ( Temp , 1 ), *Z) == 0  )) {
         *Count  =  *Count + 1 ;

       } ;
       _Px1 =  Fg_ATs ( *R ) ;
       Comptespecial ( &_Px1, & *X , & *Y , & *Z , & *Count ) ;
       _Px2 =  Fd_ATs ( *R ) ;
       Comptespecial ( &_Px2, & *X , & *Y , & *Z , & *Count ) ;

     } ;

    }
  /*---------------------------SEARCH---------------------*/
  /*----------WORD SEARCH---------*/
  /*recherecher une chaine a l'aide du triplet ( bst1,2,3)*/
  void Rechereche (string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      string255 Temp;

      /** Corps du module **/
     Temp = malloc(255 * sizeof(char));
     *Path  =  0 ;
     if( (strcmp( Caract ( *Str , 1 ), *X) == 0  ) || (strcmp( Caract ( *Str , 1 ), *X) == 0  ) || (strcmp( Caract ( *Str , 1 ), *X) == 0  )) {
       Rechmotbst1 ( & Bst1 , & *Str , & *Par , & *P , & *Path, & *X , & *Y , & *Z ) ;
       }
     else
       {
       if( (strcmp( Caract ( *Str , 1 ), *X) > 0  ) || (strcmp( Caract ( *Str , 1 ), *Y) > 0  ) || (strcmp( Caract ( *Str , 1 ), *Z) > 0  )) {
         Rechmotbst ( & Bst2 , & *Str , & *Path, & *Par , & *P ) ;
         }
       else
         {
         Rechmotbst ( & Bst3 , & *Str , & *Path, & *Par , & *P ) ;

       } ;

     } ;

    }
  /*----------------------------------------*/
  /*Rechercher une chaine STR dans un BST TR*/
  void Rechmotbst (Pointeur_ATs *Tr , Typestr_Ts *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path)
    {
      /** Variables locales **/
      bool Trouve;

      /** Corps du module **/
     *Par  =  NULL ;
     if( ( *Tr == NULL )) {
       *P  =  NULL ;
       *Path  =  0 ;
       }
     else
       {
       *P  =  *Tr ;
       *Path  =  1 ;
       Trouve  =  False ;
       while( ( *P != NULL ) && ( ! Trouve )) {
         if( (strcmp( Struct1_Ts ( Info_ATs ( *P )  ), Struct1_Ts ( *Str  )) == 0  )) {
           Trouve  =  True ;
           }
         else
           {
           *Path  =  *Path + 1 ;
           *Par  =  *P ;
           if(strcmp( Struct1_Ts ( *Str  ), Struct1_Ts ( Info_ATs ( *P )  )) < 0 ) {
             *P  =  Fg_ATs ( *Par ) ;
             }
           else
             {
             *P  =  Fd_ATs ( *Par ) ;

           } ;

         } ;

 } ;

     } ;

    }
  /*---------------------------------------*/
  void Rechmotbst1 (Pointeur_ATs *Tr , Typestr_Ts *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      string255 Temp;
      bool Trouve;

      /** Corps du module **/
     Temp = malloc(255 * sizeof(char));
     *Par  =  NULL ;
     if( ( *Tr == NULL )) {
       *P  =  NULL ;
       *Path  =  0 ;
       }
     else
       {
       *P  =  *Tr ;
       *Path  =  1 ;
       Trouve  =  False ;
       while( ( *P != NULL ) && ( ! Trouve )) {
         if( (strcmp( Struct1_Ts ( Info_ATs ( *P )  ), Struct1_Ts ( *Str  )) == 0  )) {
           Trouve  =  True ;
          /*arret au premier mot non-special*/
           }
         else
           {
           strcpy (Temp,   Struct1_Ts ( Info_ATs ( *P )  )) ;
           if( (strcmp( Caract ( Temp , 1 ), *X) != 0  ) && (strcmp( Caract ( Temp , 1 ), *Y) != 0  ) && (strcmp( Caract ( Temp , 1 ), *Z) != 0  )) {
             *P  =  NULL ;
             }
           else
             {
             *Par  =  *P ;
             *Path  =  *Path + 1 ;
             if(strcmp( Struct1_Ts ( *Str  ), Struct1_Ts ( Info_ATs ( *P )  )) < 0 ) {
               *P  =  Fg_ATs ( *Par ) ;
               }
             else
               {
               *P  =  Fd_ATs ( *Par ) ;

             } ;

           } ;

         } ;

 } ;

     } ;

    }
  /*----------------------Range search---------------------------*/
  /*-----generer le fichier ------*/
  void Genererfichier (FILE *F , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int J;
      int I;
      string255 Word;
      Type_Ts S_S;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Word = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "N" ) ;
     for( J  =  1 ;J <=  5 ; ++J){
       Randword ( & Word , & I , & *A , & *B , & *C ) ;
       S_S.Champ1= malloc(255 * sizeof(char));
       strcpy(S_S.Champ1 , Word) ;
       Init_struct_Ts ( S , S_S )  ;
       Ecrireseq_s ( F , S );
     } ;
     Fermer_s ( F ) ;

    }
  /*genere des mots aleatoires*/
  void Randword (string255 *Word , int *I , string255 *A , string255 *B , string255 *C)
    {
      /** Variables locales **/
      string255 _Sx;

      /** Corps du module **/
     _Sx = malloc(255 * sizeof(char));
     *I  =  Aleanombre(10 ) ;
     if( *I == 0) {
       strcpy (_Sx, *A);
       strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
       }
     else
       {
       if( *I == 1) {
         strcpy (_Sx, *B);
         strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
         }
       else
         {
         if( *I == 2) {
           strcpy (_Sx, *C);
           strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
           }
         else
           {
           strcpy (*Word,   Aleachaine(Aleanombre(5 ) + 3 )) ;

         } ;

       } ;

     } ;

    }
  void Libererarb (Pointeur_ATs *R)
    {
      /** Variables locales **/
      Pointeur_ATs Tempgauche=NULL;
      Pointeur_ATs Tempdroit=NULL;

      /** Corps du module **/
     if( ( *R != NULL )) {
       Tempgauche  =  Fg_ATs ( *R ) ;
       Tempdroit  =  Fd_ATs ( *R ) ;
       Libererarb ( & Tempgauche ) ;
       Libererarb ( & Tempdroit ) ;
       Liberernoeud_ATs ( *R ) ;

     } ;

    }
  void Preordre (Pointeur_ATs *R)
    {
      /** Variables locales **/
      Type_Ts _Struct_Temp3;
      Pointeur_ATs _Px1=NULL;
      Pointeur_ATs _Px2=NULL;

      /** Corps du module **/
     if( ( *R != NULL )) {
       /** Ecriture d'une structure */
       _Struct_Temp3 = *Info_ATs(*R);
       printf ( " %s", _Struct_Temp3.Champ1 ) ;
       _Px1 =  Fg_ATs ( *R ) ;
       Preordre ( &_Px1) ;
       _Px2 =  Fd_ATs ( *R ) ;
       Preordre ( &_Px2) ;

     } ;

    }

  int main(int argc, char *argv[])
    {
     srand(time(NULL));
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     X = malloc(2 * sizeof(char));
     Y = malloc(2 * sizeof(char));
     Z = malloc(2 * sizeof(char));
     printf(" Entrer la premiere lettre : ");
     scanf ( " %s", X ) ;
     printf("\n Entrer la deuxieme lettre : ");
     scanf ( " %s", Y ) ;
     printf("\n Entrer la troisieme lettre : ");
     scanf ( " %s", Z ) ;
     Genererfichier ( & Fich , & X , & Y , & Z ) ;
     Constructbst1 ( & Fich , & Bst1 , & X , & Y , & Z ) ;
     Constructbst3 ( & Fich , & Bst3 , & X , & Y , & Z ) ;
     Constructbst3 ( & Fich , & Bst2 , & X , & Y , & Z ) ;
     Quitter  =  False ;
     while( ( ! Quitter )) {
       clear_screen();
       printf ( " %s", "\n" ) ;
       printf ( " %s", "-------------------------------------------------------\n" ) ;
       printf ( " %s", "                          MENU                         \n" ) ;
       printf ( " %s", "-------------------------------------------------------\n" ) ;
       printf ( " %s", " 1. Parcours Inordre des arbres              \n" ) ;
       printf ( " %s", " 2. Compter les mots commencant par X / Y / Z \n" ) ;
       printf ( " %s", " 3. Compter les mots par niveau              \n" ) ;
       printf ( " %s", " 4. Hauteur des arbres                       \n" ) ;
       printf ( " %s", " 5. Quitter                                  \n" ) ;
       printf ( " %s", "-------------------------------------------------------\n" ) ;
       printf ( " %s", ">> Choisissez une option : " ) ;
       scanf ( " %d", &Choix ) ;
       printf ( " %s", "\n" ) ;
       if( ( Choix == 1 )) {
         printf ( " %s", "PARCOURS INORDRE DU BST  \n" ) ;
         Inordre ( & Bst1 ) ;
         getchar();
         printf("\n Appuyer sur entrer pour continuer..");
         getchar();
         }
       else
         {
         if( ( Choix == 2 )) {
           Num  =  0 ;
           Comptespecial ( & Bst1 , & X , & Y , & Z , & Num ) ;
           printf ( " %s", "Nombre de Mots commencant par X , Y ou Z : " );
           printf ( " %d", Num ) ;
           printf ( " %s", "\n" ) ;
           getchar();
            printf("\n Appuyer sur entrer pour continuer..");
         getchar();
           }
         else
           {
           if( ( Choix == 3 )) {
             printf ( " %s", "Nombre De Mots commencant par X , Y ou Z Dans Chaque Niveau:\n" ) ;
             printf ( " %s", "BST1:\n" ) ;
             Affich_niv ( & Bst1 , & X , & Y , & Z ) ;
             printf ( " %s", "BST2:\n" ) ;
             Affich_niv ( & Bst2 , & X , & Y , & Z ) ;
             printf ( " %s", "BST3:\n" ) ;
             Affich_niv ( & Bst3 , & X , & Y , & Z ) ;
             getchar();
                      printf("\n Appuyer sur entrer pour continuer..");
         getchar();
             }
           else
             {
             if( ( Choix == 4 )) {
               printf ( " %s", "Hauteur du BST1 :" );
               printf ( " %d", Height(&Bst1) ) ;
               printf ( " %s", "\n" ) ;
               printf ( " %s", "Hauteur du BST2 :" );
               printf ( " %d", Height(&Bst2) ) ;
               printf ( " %s", "\n" ) ;
               printf ( " %s", "Hauteur du BST3 :" );
               printf ( " %d", Height(&Bst3) ) ;
               printf ( " %s", "\n" ) ;
               Preordre ( & Bst1 ) ;
               getchar();
                        printf("\n Appuyer sur entrer pour continuer..");
         getchar();
               }
             else
               {
               if( ( Choix == 5 )) {
                 printf ( " %s", "Fin du programme.\n" ) ;
                 Quitter  =  True ;
                 getchar();
                          printf("\n Appuyer sur entrer pour continuer..");
         getchar();
                 }
               else
                 {
                 printf ( " %s", "Option invalide. Veuillez choisir une option entre 1 et 5.\n" ) ;
                 getchar();
                          printf("\n Appuyer sur entrer pour continuer..");
         getchar();
               } ;
             } ;
           } ;
         } ;
       }
 } ;
     Libererarb ( & Bst1 ) ;
     Libererarb ( & Bst2 ) ;
     Libererarb ( & Bst3 ) ;
      system("PAUSE");
      return 0;
    }
