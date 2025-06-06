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
      else printf ("%s\n", "Pile vide");
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
      else printf ("%s\n", "File d'attente vide");
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
      else printf ("%s\n", "File d'attente vide");
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
  Pointeur_ATs Bst0=NULL;

  Pointeur_ATs P=NULL;
  Pointeur_ATs Par=NULL;
  FILE *Fich;
  Typestruct1_s S ;
  string2 X;
  string2 Y;
  string2 Z;
  int Choix;
  int Num;
  bool Quitter;
  string255 Str;
  int N;
  Type_Ts _Struct_Temp1;
  Type_Ts _Struct_Temp2;

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
      strcpy( S->Champ1 , S_.Champ1 );
    }


  /** Prototypes des fonctions **/

  void Constructbst2 (FILE *F , char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  void Constructbst0 (FILE *F ,char *file_name , Pointeur_ATs *Tree);
  void Vers_milieu (Pointeur_ATs *R , Pointeur_ATs *P);
  void Rangequery_optimal (Pointeur_ATs *Bst1 , Pointeur_ATs *Bst2 , Pointeur_ATs *Bst3 , string2 *X , string2 *Y , string2 *Z , int *N);
  void Rangequery (Pointeur_ATs *Tr , string255 *Mini , string255 *Maxi , int *N);
  void Constructbst1 (FILE *F ,char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  void Constructbst3 (FILE *F ,char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C);
  Pointeur_ATs Insertbst (Pointeur_ATs *Tr , string255 *Str ,bool *found) ;
  Pointeur_ATs Rotdroite (Pointeur_ATs *P) ;
  Pointeur_ATs Rotgauche (Pointeur_ATs *P) ;
  void Vers_racine (Pointeur_ATs *R , Pointeur_ATs *P);
  void Inordre (Pointeur_ATs *Tr);
  int  Height (Pointeur_ATs *Tr) ;
  void Affich_niv (Pointeur_ATs *R , string2 *A , string2 *B , string2 *C);
  void Comptespecial (Pointeur_ATs *R , string2 *X , string2 *Y , string2 *Z , int *Count);
  void Recherche (string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z);
  void Rechmotbst (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path);
  void Rechmotbst1 (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z);
  void Rechmotbst3 (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z);
  void Genererfichier (FILE *F ,char *file_name  ,string2 *A , string2 *B , string2 *C , int n);
  void Randword (string255 *Word , int *I , string255 *A , string255 *B , string255 *C);
  void Libererarb (Pointeur_ATs *R);
  void Preordre (Pointeur_ATs *R);
  void sim_range_query_once(char *file_name, string2 A, string2 B, string2 C);
  void sim_range_query_10(char *file_name, string2 A, string2 B, string2 C);

  /*---------------------------MODULES-----------------------------------*/
  /*---------CONSTRUCTION-------------------*/

    void Constructbst0 (FILE *F ,char *file_name , Pointeur_ATs *Tree)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 _Px1;
      bool trv;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     _Px1 = malloc(255 * sizeof(char));
     Ouvrir_s (&F , file_name , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy(_Px1,  Struct1_Ts ( S  ) );
       P  =  Insertbst ( & *Tree , &_Px1 ,&trv) ;
      /*incrementer le compteur */
       if( ( P != NULL )) {
         Nodesnum  =  Nodesnum + 1 ;
       } ;

      } ;
     Fermer_s ( F ) ;

    }

  void Constructbst2 (FILE *F ,char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;
      string255 _Px1;
      bool trv;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     _Px1 = malloc(255 * sizeof(char));
     Ouvrir_s (&F , file_name , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy(_Px1,  Struct1_Ts ( S  ) );
       trv = False;
       P  =  Insertbst ( & *Tree , &_Px1 , &trv) ;
      /*incrementer le compteur */
       if( ( P != NULL ) && (!trv)) {
         Nodesnum  =  Nodesnum + 1 ;
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) == 0  ) || (strcmp( Caract ( Str , 1 ), *B) == 0  ) || (strcmp( Caract ( Str , 1 ), *C) == 0  )) {
           Vers_milieu ( & *Tree , & P ) ;

         } ;

       } ;

 } ;
     Fermer_s ( F ) ;

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
  void Rangequery_optimal (Pointeur_ATs *Bst1 , Pointeur_ATs *Bst2 , Pointeur_ATs *Bst3 , string2 *X , string2 *Y , string2 *Z , int *N)
    {
      /** Variables locales **/
      string255 Mini;
      string255 Maxi;
      int N1;
      int N2;
      int N3;
      string2 Mini_char;
      string2 Maxi_char;

      /** Corps du module **/
     Mini = malloc(255 * sizeof(char));
     Maxi = malloc(255 * sizeof(char));
     Mini_char = malloc(2 * sizeof(char));
     Maxi_char = malloc(2 * sizeof(char));
     printf ( "%s", " ENTRER LE MOT MINIMUM: " ) ;
     scanf ( " %[^\n]", Mini ) ;
     getchar();
     printf ( "%s", " ENTRER LE MOT MAXIMUM: " ) ;
     scanf ( " %[^\n]", Maxi ) ;
     printf("\n");
     getchar();
     strcpy (Mini_char,   Caract ( Mini , 1 )) ;
     strcpy (Maxi_char,   Caract ( Maxi , 1 )) ;
     if( ( (strcmp( Mini_char, *X) == 0  ) || (strcmp( Mini_char, *Y) == 0  ) || (strcmp( Mini_char, *Z) == 0  ) ) && ( (strcmp( Maxi_char, *X) == 0  ) || (strcmp( Maxi_char, *Y) == 0  ) || (strcmp( Maxi_char, *Z) == 0  ) )) {
       printf ( "%s\n", " USING BST1 - SPECIAL CHARS AT ROOT\n" ) ;
       Rangequery ( & *Bst1 , & Mini , & Maxi , & *N ) ;
       }
     else
       {
       if( ( (strcmp( Mini_char, *X) != 0  ) && (strcmp( Mini_char, *Y) != 0  ) && (strcmp( Mini_char, *Z) != 0  ) ) && ( (strcmp( Maxi_char, *X) != 0  ) && (strcmp( Maxi_char, *Y) != 0  ) && (strcmp( Maxi_char, *Z) != 0  ) )) {
         printf ( "%s\n", " USING BST3 - NON-SPECIAL CHARS AT ROOT\n" ) ;
         Rangequery ( & *Bst3 , & Mini , & Maxi , & *N ) ;
         }
       else
         {
         printf ( "%s\n", " USING BST2 - BALANCED TREE\n" ) ;
         Rangequery ( & *Bst2 , & Mini , & Maxi , & *N ) ;

       }
     } ;
     printf ( "%s", "\n NUMBER OF NODES VISITED: " ) ;
     printf ( "%d\n", *N ) ;

    }
  void Rangequery (Pointeur_ATs *Tr , string255 *Mini , string255 *Maxi , int *N)
    {
      /** Variables locales **/
      Pointeur_ATs P=NULL;
      Pointeur_ATs Q=NULL;
      bool Notempty;
      Pointeur_PATs Pil=NULL;
      string255 Str;
      int Cpt;
      Type_Ts _Struct_Temp3;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     *N  =  0 ;
     Creerpile_PATs (& Pil ) ;
     P  =  *Tr ;
     Cpt  =  0 ;
     Notempty  =  True ;
     while( Notempty)  {
       while( P != NULL)  {
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if(strcmp( Str, *Mini) >= 0 )   {
           Empiler_PATs (& Pil , P ) ;
           P  =  Fg_ATs ( P ) ;
           *N  =  *N + 1 ;
           }
         else
           {
           P  =  Fd_ATs ( P ) ;
           *N  =  *N + 1 ;

         } ;

 } ;
       if( ! Pilevide_PATs ( Pil ))   {
         Depiler_PATs (& Pil , &P ) ;
         *N  =  *N + 1 ;
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Str, *Mini) >= 0  ) && (strcmp( Str, *Maxi) <= 0  ))   {
           /** Ecriture d'une structure */
           _Struct_Temp3 = *Info_ATs(P);
           printf ( " %s\n", _Struct_Temp3.Champ1 ) ;
           Cpt  =  Cpt + 1 ;

         } ;
         if(strcmp( Str, *Maxi) <= 0 )   {
           P  =  Fd_ATs ( P ) ;
           }
         else
           {
           P  =  NULL ;

         } ;
         }
       else
         {
         Notempty  =  False;
       }
 } ;
     printf ( "%s", "\n NUMBER OF WORDS FOUND :" ) ;
     printf ( " %d\n", Cpt ) ;

    }
  /*construction du BST1 a partir du fichier genere*/
  void Constructbst1 (FILE *F ,char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {

      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;
      string255 _Px1;
      bool trv;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     _Px1 = malloc(255 * sizeof(char));

     Ouvrir_s (&F , file_name , "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy(_Px1,  Struct1_Ts ( S  ) );
       P  =  Insertbst ( & *Tree , &_Px1 ,&trv) ;
      /*incrementer le compteur */
       if( ( P != NULL ) && !trv) {
         Nodesnum  =  Nodesnum + 1 ;
        /*si une chaine speciale , deplacer vers la racine */
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) == 0  ) || (strcmp( Caract ( Str , 1 ), *B) == 0  ) || (strcmp( Caract ( Str , 1 ), *C) == 0  )) {
           Vers_racine ( & *Tree , & P ) ;

         } ;

       } ;

      } ;
     Fermer_s ( F ) ;

    }
  /*--------------------------------------------*/
  void Constructbst3 (FILE *F ,char *file_name , Pointeur_ATs *Tree , string2 *A , string2 *B , string2 *C)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int Nodesnum;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      string255 Str;
      string255 _Px1;
      bool trv ;

      /** Corps du module **/
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     Str = malloc(255 * sizeof(char));
     _Px1 = malloc(255 * sizeof(char));
     Ouvrir_s (&F , file_name, "A" ) ;
     Nodesnum  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy(_Px1,  Struct1_Ts ( S  ) );
       P  =  Insertbst ( & *Tree , &_Px1 , &trv) ;
      /*incrementer le compteur */
       if( ( P != NULL ) && !trv) {
         Nodesnum  =  Nodesnum + 1 ;
        /*si une chaine speciale , deplacer vers la racine */
         strcpy (Str,   Struct1_Ts ( Info_ATs ( P )  )) ;
         if( (strcmp( Caract ( Str , 1 ), *A) != 0  ) && (strcmp( Caract ( Str , 1 ), *B) != 0  ) && (strcmp( Caract ( Str , 1 ), *C) != 0  )) {
           Vers_racine ( & *Tree , & P ) ;

         } ;

       } ;

 } ;
     Fermer_s ( F ) ;
    }
  /*--------------------------------*/
  /*inserer un noeud dans le BST*/
  Pointeur_ATs Insertbst (Pointeur_ATs *Tr , string255 *Str ,bool *found)
    {
      /** Variables locales **/
      Pointeur_ATs Insertbst2 =NULL;
      Pointeur_ATs N=NULL;
      Pointeur_ATs P=NULL;
      Pointeur_ATs Par=NULL;
      Typestr_Ts Cont;
      int Temp;
      Type_Ts S_Cont;


      /** Corps du module **/
     *found = False;
     Cont = malloc(sizeof(Type_Ts));
     Cont->Champ1 = malloc(255 * sizeof(char));
     Rechmotbst ( & *Tr , & *Str , & Par , & N , & Temp ) ;
    /*si la chaine n'existe pas deja*/
     if( ( N == NULL )) {
       Creernoeud_ATs (& N ) ;
       S_Cont.Champ1= malloc(255 * sizeof(char));
       strcpy(S_Cont.Champ1 , *Str) ;
       Init_struct_Ts ( Cont , S_Cont )  ;
       Aff_info_ATs ( N , Cont ) ;
       Aff_pere_ATs ( N , Par ) ;
       if( ( *Tr == NULL )) {
         *Tr  =  N ;
         }
       else
         {
         if( (strcmp( *Str, Struct1_Ts ( Info_ATs ( Par )  )) > 0  )) {
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
       *found = True;

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
      Type_Ts _Struct_Temp4;

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
         _Struct_Temp4 = *Info_ATs(P);
         printf ( " %s\n", _Struct_Temp4.Champ1 ) ;
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
           printf ( " %s\n", "ELEMENT:" );
           printf ( " %s\n", Str );
           printf ( " %s\n", "NIVEAU" );
           printf ( " %d\n", Niv ) ;

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
         printf ( " %s\n", "niveau" );
         printf ( " %d\n", I );
         printf ( " %s\n", "nombre" );
         printf ( " %d\n", Element_V50i(T,I) ) ;

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
  void Recherche (string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      string255 Temp;

      /** Corps du module **/
     Temp = malloc(255 * sizeof(char));
     *Path  =  0 ;
     if( (strcmp( Caract ( *Str , 1 ), *X) == 0  ) || (strcmp( Caract ( *Str , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Str , 1 ), *Z) == 0  )) {
       Rechmotbst1 ( & Bst1 , & *Str , & *Par , & *P , & *Path , & *X , & *Y , & *Z ) ;
       }
     else
       {
       if( (strcmp( Caract ( *Str , 1 ), *X) > 0  ) || (strcmp( Caract ( *Str , 1 ), *Y) > 0  ) || (strcmp( Caract ( *Str , 1 ), *Z) > 0  )) {
         Rechmotbst ( & Bst2 , & *Str , & *Par , & *P , & *Path ) ;
         }
       else
         {
         Rechmotbst3 ( & Bst3 , & *Str , & *Par , & *P , & *Path , & *X , & *Y , & *Z ) ;

       } ;

     } ;

    }
  /*----------------------------------------*/
  /*Rechercher une chaine STR dans un BST TR*/
  void Rechmotbst (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path)
    {
      /** Variables locales **/
      bool Trouve;

      /** Corps du module **/

     *Par  =  NULL ;

     if( Tr == NULL ) {
       *P  =  NULL ;
       *Path  =  0 ;

       }
     else
       {
       *P  =  *Tr ;
       *Path  =  1 ;
       Trouve  =  False ;

       while( ( *P != NULL ) && ( ! Trouve )) {
         if( (strcmp( Struct1_Ts ( Info_ATs ( *P )  ), *Str) == 0  )) {
           Trouve  =  True ;
           }
         else
           {
           *Path  =  *Path + 1 ;
           *Par  =  *P ;
           if(strcmp( *Str, Struct1_Ts ( Info_ATs ( *P )  )) < 0 ) {
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
  void Rechmotbst1 (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z)
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
         if( (strcmp( Struct1_Ts ( Info_ATs ( *P )  ), *Str) == 0  )) {
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
             if(strcmp( *Str, Struct1_Ts ( Info_ATs ( *P )  )) < 0 ) {
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
  /*---------------------------------------*/
  void Rechmotbst3 (Pointeur_ATs *Tr , string255 *Str , Pointeur_ATs *Par , Pointeur_ATs *P , int *Path , string2 *X , string2 *Y , string2 *Z)
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
         if( (strcmp( Struct1_Ts ( Info_ATs ( *P )  ), *Str) == 0  )) {
           Trouve  =  True ;
          /*arret au premier mot special*/
           }
         else
           {
           strcpy (Temp,   Struct1_Ts ( Info_ATs ( *P )  )) ;
           if( (strcmp( Caract ( Temp , 1 ), *X) == 0  ) || (strcmp( Caract ( Temp , 1 ), *Y) == 0  ) || (strcmp( Caract ( Temp , 1 ), *Z) == 0  )) {
             *P  =  NULL ;
             }
           else
             {
             *Par  =  *P ;
             *Path  =  *Path + 1 ;
             if(strcmp( *Str, Struct1_Ts ( Info_ATs ( *P )  )) < 0 ) {
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
  void Genererfichier (FILE *F ,char *file_name  ,string2 *A , string2 *B , string2 *C , int n)
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
     Ouvrir_s (&F , file_name , "N" ) ;
     for( J  =  1 ;J <=  n ; ++J){
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
       strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(10) + 3 ))) ;
       }
     else
       {
       if( *I == 1) {
         strcpy (_Sx, *B);
         strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(10) + 3 ))) ;
         }
       else
         {
         if( *I == 2) {
           strcpy (_Sx, *C);
           strcpy (*Word,  strcat(_Sx, Aleachaine(Aleanombre(10) + 3 ))) ;
           }
         else
           {
           strcpy (*Word,   Aleachaine(Aleanombre(10) + 3 )) ;

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
/*------------------------SIMULATION--------------------------------*/

void sim_range_query_10(char *file_name, string2 A, string2 B, string2 C) {
    char txt_file_name[256];
    strcpy(txt_file_name, file_name);
    char *dot = strrchr(txt_file_name, '.');
    if(dot) *dot = '\0';
    strcat(txt_file_name, ".txt");

    FILE *words_file, *pairs_file, *result;
    int accumulated_temp[3][2][4];
    int total_results[10][3][2][4];

    result = fopen(txt_file_name, "w");

    fprintf(result, "Run | Search Type     | BST0_Special | BST0_Higher  | BST0_Lower   | BST0_Total   | 3BST_Special | 3BST_Higher  | 3BST_Lower   | 3BST_Total   |\n");
    fprintf(result, "----+-----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");

    const char* search_type_names[3] = {
        "Range Found    ",
        "Range Not Found",
        "All Queries    "
    };

    for(int run = 0; run < 10; run++) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 4; k++) {
                    accumulated_temp[i][j][k] = 0;
                }
            }
        }

        Genererfichier(words_file, "words_10000.z", &A, &B, &C, 10000);
        Genererfichier(pairs_file, "pairs_5000.z", &A, &B, &C, 10000);

        printf("Run %d: Files generated successfully - 10000 words and 5000 pairs\n", run+1);

        Constructbst1(words_file, "words_10000.z", &Bst1, &A, &B, &C);
        Constructbst2(words_file, "words_10000.z", &Bst2, &A, &B, &C);
        Constructbst3(words_file, "words_10000.z", &Bst3, &A, &B, &C);
        Constructbst0(words_file, "words_10000.z", &Bst0);

        Typestruct1_s S;
        string255 min_word, max_word;
        string255 _Px1;

        S = malloc(sizeof(Typestruct1_s));
        S->Champ1 = malloc(255 * sizeof(char));
        min_word = malloc(255 * sizeof(char));
        max_word = malloc(255 * sizeof(char));
        _Px1 = malloc(255 * sizeof(char));

        Ouvrir_s(&pairs_file, "pairs_5000.z", "A");

        int pair_count = 0;
        while(!Finfich_s(pairs_file) && pair_count < 5000) {
            if(!Finfich_s(pairs_file)) {
                Lireseq_s(pairs_file, S);
                strcpy(min_word, Struct1_Ts(S));
            }

            if(!Finfich_s(pairs_file)) {
                Lireseq_s(pairs_file, S);
                strcpy(max_word, Struct1_Ts(S));
            }

            if(strcmp(min_word, max_word) > 0) {
                strcpy(_Px1, min_word);
                strcpy(min_word, max_word);
                strcpy(max_word, _Px1);
            }

            string255 mini_copy = malloc(255 * sizeof(char));
            string255 maxi_copy = malloc(255 * sizeof(char));
            strcpy(mini_copy, min_word);
            strcpy(maxi_copy, max_word);

            int N_triplet = 0;
            int words_found_triplet = 0;
            Rangequery_optimal_param(&Bst1, &Bst2, &Bst3, &mini_copy, &maxi_copy, &A, &B, &C, &N_triplet, &words_found_triplet);

            int N_bst0 = 0;
            int words_found_bst0 = Rangequery_param(&Bst0, &mini_copy, &maxi_copy, &N_bst0);

            string2 min_char = malloc(2 * sizeof(char));
            strcpy(min_char, Caract(min_word, 1));

            int category = 0;
            bool min_is_special = (strcmp(min_char, A) == 0 || strcmp(min_char, B) == 0 || strcmp(min_char, C) == 0);
            bool min_gt_special = (strcmp(min_char, A) > 0 || strcmp(min_char, B) > 0 || strcmp(min_char, C) > 0);

            if(min_is_special) {
                category = 0;
            } else if(min_gt_special) {
                category = 1;
            } else {
                category = 2;
            }

            if(words_found_bst0 > 0) {
                accumulated_temp[0][0][category] += N_bst0;
            } else {
                accumulated_temp[1][0][category] += N_bst0;
            }

            if(words_found_triplet > 0) {
                accumulated_temp[0][1][category] += N_triplet;
            } else {
                accumulated_temp[1][1][category] += N_triplet;
            }

            free(mini_copy);
            free(maxi_copy);
            free(min_char);

            pair_count++;
        }

        for(int search_type = 0; search_type < 2; search_type++) {
            for(int tree = 0; tree < 2; tree++) {
                accumulated_temp[search_type][tree][3] = accumulated_temp[search_type][tree][0] +
                                                       accumulated_temp[search_type][tree][1] +
                                                       accumulated_temp[search_type][tree][2];
            }
        }

        for(int tree = 0; tree < 2; tree++) {
            for(int cat = 0; cat < 4; cat++) {
                accumulated_temp[2][tree][cat] = accumulated_temp[0][tree][cat] + accumulated_temp[1][tree][cat];
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 4; k++) {
                    total_results[run][i][j][k] = accumulated_temp[i][j][k];
                }
            }
        }

        printf("\nRun %d Results:\n", run+1);
        printf("+-----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");
        printf("| Search Type     | BST0_Special | BST0_Higher  | BST0_Lower   | BST0_Total   | 3BST_Special | 3BST_Higher  | 3BST_Lower   | 3BST_Total   |\n");
        printf("+-----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");

        for(int i = 0; i < 3; i++) {
            printf("| %-15s ", search_type_names[i]);
            for(int j = 0; j <= 3; j++) {
                printf("| %-12d ", accumulated_temp[i][0][j]);
            }
            for(int j = 0; j <= 3; j++) {
                printf("| %-12d ", accumulated_temp[i][1][j]);
            }
            printf("|\n");
        }
        printf("+-----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n\n");

        free(S->Champ1);
        free(S);
        free(min_word);
        free(max_word);
        free(_Px1);

        Fermer_s(pairs_file);
    }

    for(int run = 0; run < 10; run++) {
        for(int i = 0; i < 3; i++) {
            fprintf(result, "%3d | %-15s |", run+1, search_type_names[i]);

            for(int j = 0; j <= 3; j++) {
                fprintf(result, " %-12d |", total_results[run][i][0][j]);
            }

            for(int j = 0; j <= 3; j++) {
                fprintf(result, " %-12d |", total_results[run][i][1][j]);
            }

            fprintf(result, "\n");
        }
        if(run < 9) {
            fprintf(result, "----+-----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");
        }
    }

    fclose(result);
    printf("Range query test completed - Results saved to %s\n", txt_file_name);
}
void sim_range_query_once(char *file_name, string2 A, string2 B, string2 C) {
    char txt_file_name[256];
    strcpy(txt_file_name, file_name);
    char *dot = strrchr(txt_file_name, '.');
    if(dot) *dot = '\0';
    strcat(txt_file_name, ".txt");

    FILE *words_file, *pairs_file, *result;
    int accumulated_temp[3][2][4];

    result = fopen(txt_file_name, "w");

    fprintf(result, "Search Type     | BST0_Special | BST0_Higher  | BST0_Lower   | BST0_Total   | 3BST_Special | 3BST_Higher  | 3BST_Lower   | 3BST_Total   |\n");
    fprintf(result, "----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");

    printf("Search Type     | BST0_Special | BST0_Higher  | BST0_Lower   | BST0_Total   | 3BST_Special | 3BST_Higher  | 3BST_Lower   | 3BST_Total   |\n");
    printf("----------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n");

    const char* search_type_names[3] = {
        "Range Found    ",
        "Range Not Found",
        "All Queries    "
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 4; k++) {
                accumulated_temp[i][j][k] = 0;
            }
        }
    }

    Genererfichier(words_file, "words_10000.z", &A, &B, &C, 10000);
    Genererfichier(pairs_file, "pairs_5000.z", &A, &B, &C, 10000);

    Constructbst1(words_file, "words_10000.z", &Bst1, &A, &B, &C);
    Constructbst2(words_file, "words_10000.z", &Bst2, &A, &B, &C);
    Constructbst3(words_file, "words_10000.z", &Bst3, &A, &B, &C);
    Constructbst0(words_file, "words_10000.z", &Bst0);

    Typestruct1_s S;
    string255 min_word, max_word;
    string255 _Px1;

    S = malloc(sizeof(Typestruct1_s));
    S->Champ1 = malloc(255 * sizeof(char));
    min_word = malloc(255 * sizeof(char));
    max_word = malloc(255 * sizeof(char));
    _Px1 = malloc(255 * sizeof(char));

    Ouvrir_s(&pairs_file, "pairs_5000.z", "A");

    int pair_count = 0;
    while(!Finfich_s(pairs_file) && pair_count < 5000) {
        if(!Finfich_s(pairs_file)) {
            Lireseq_s(pairs_file, S);
            strcpy(min_word, Struct1_Ts(S));
        }

        if(!Finfich_s(pairs_file)) {
            Lireseq_s(pairs_file, S);
            strcpy(max_word, Struct1_Ts(S));
        }

        if(strcmp(min_word, max_word) > 0) {
            strcpy(_Px1, min_word);
            strcpy(min_word, max_word);
            strcpy(max_word, _Px1);
        }

        string255 mini_copy = malloc(255 * sizeof(char));
        string255 maxi_copy = malloc(255 * sizeof(char));
        strcpy(mini_copy, min_word);
        strcpy(maxi_copy, max_word);

        int N_triplet = 0;
        int words_found_triplet = 0;
        Rangequery_optimal_param(&Bst1, &Bst2, &Bst3, &mini_copy, &maxi_copy, &A, &B, &C, &N_triplet, &words_found_triplet);

        int N_bst0 = 0;
        int words_found_bst0 = Rangequery_param(&Bst0, &mini_copy, &maxi_copy, &N_bst0);

        string2 min_char = malloc(2 * sizeof(char));
        strcpy(min_char, Caract(min_word, 1));

        int category = 0;
        bool min_is_special = (strcmp(min_char, A) == 0 || strcmp(min_char, B) == 0 || strcmp(min_char, C) == 0);
        bool min_gt_special = (strcmp(min_char, A) > 0 || strcmp(min_char, B) > 0 || strcmp(min_char, C) > 0);

        if(min_is_special) {
            category = 0;
        } else if(min_gt_special) {
            category = 1;
        } else {
            category = 2;
        }

        if(words_found_bst0 > 0) {
            accumulated_temp[0][0][category] += N_bst0;
        } else {
            accumulated_temp[1][0][category] += N_bst0;
        }

        if(words_found_triplet > 0) {
            accumulated_temp[0][1][category] += N_triplet;
        } else {
            accumulated_temp[1][1][category] += N_triplet;
        }

        free(mini_copy);
        free(maxi_copy);
        free(min_char);

        pair_count++;
    }

    for(int search_type = 0; search_type < 2; search_type++) {
        for(int tree = 0; tree < 2; tree++) {
            accumulated_temp[search_type][tree][3] = accumulated_temp[search_type][tree][0] +
                                                   accumulated_temp[search_type][tree][1] +
                                                   accumulated_temp[search_type][tree][2];
        }
    }

    for(int tree = 0; tree < 2; tree++) {
        for(int cat = 0; cat < 4; cat++) {
            accumulated_temp[2][tree][cat] = accumulated_temp[0][tree][cat] + accumulated_temp[1][tree][cat];
        }
    }

    for(int i = 0; i < 3; i++) {
        fprintf(result, "%-15s |", search_type_names[i]);
        printf("%-15s |", search_type_names[i]);

        for(int j = 0; j <= 3; j++) {
            fprintf(result, " %-12d |", accumulated_temp[i][0][j]);
            printf(" %-12d |", accumulated_temp[i][0][j]);
        }

        for(int j = 0; j <= 3; j++) {
            fprintf(result, " %-12d |", accumulated_temp[i][1][j]);
            printf(" %-12d |", accumulated_temp[i][1][j]);
        }

        fprintf(result, "\n");
        printf("\n");
    }

    free(S->Champ1);
    free(S);
    free(min_word);
    free(max_word);
    free(_Px1);

    Fermer_s(pairs_file);
    fclose(result);
}

void Rangequery_optimal_param(Pointeur_ATs *Bst1, Pointeur_ATs *Bst2, Pointeur_ATs *Bst3,
                              string255 *Mini, string255 *Maxi, string2 *X, string2 *Y, string2 *Z, int *N, int *words_found) {
    string2 Mini_char;
    string2 Maxi_char;

    Mini_char = malloc(2 * sizeof(char));
    Maxi_char = malloc(2 * sizeof(char));

    strcpy(Mini_char, Caract(*Mini, 1));
    strcpy(Maxi_char, Caract(*Maxi, 1));

    if(((strcmp(Mini_char, *X) == 0) || (strcmp(Mini_char, *Y) == 0) || (strcmp(Mini_char, *Z) == 0)) &&
       ((strcmp(Maxi_char, *X) == 0) || (strcmp(Maxi_char, *Y) == 0) || (strcmp(Maxi_char, *Z) == 0))) {
        // Using BST1 - Special chars at root
        *words_found = Rangequery_param(&*Bst1, Mini, Maxi, N);
    }
    else if(((strcmp(Mini_char, *X) != 0) && (strcmp(Mini_char, *Y) != 0) && (strcmp(Mini_char, *Z) != 0)) &&
            ((strcmp(Maxi_char, *X) != 0) && (strcmp(Maxi_char, *Y) != 0) && (strcmp(Maxi_char, *Z) != 0))) {
        // Using BST3 - Non-special chars at root
        *words_found = Rangequery_param(&*Bst3, Mini, Maxi, N);
    }
    else {
        // Using BST2 - Balanced tree
        *words_found = Rangequery_param(&*Bst2, Mini, Maxi, N);
    }

    free(Mini_char);
    free(Maxi_char);
}

int Rangequery_param(Pointeur_ATs *Tr, string255 *Mini, string255 *Maxi, int *N) {
    Pointeur_ATs P = NULL;
    bool Notempty;
    Pointeur_PATs Pil = NULL;
    string255 Str;
    int Cpt;
    Type_Ts *StructTemp3;

    Str = malloc(255 * sizeof(char));
    *N = 0;
    Creerpile_PATs(&Pil);
    P = *Tr;
    Cpt = 0;
    Notempty = True;

    while(Notempty) {
        while(P != NULL) {
            strcpy(Str, Struct1_Ts(Info_ATs(P)));
            if(strcmp(Str, *Mini) >= 0) {
                Empiler_PATs(&Pil, P);
                P = Fg_ATs(P);
                *N = *N + 1;
            }
            else {
                P = Fd_ATs(P);
                *N = *N + 1;
            }
        }

        if(!Pilevide_PATs(Pil)) {
            Depiler_PATs(&Pil, &P);
            *N = *N + 1;
            strcpy(Str, Struct1_Ts(Info_ATs(P)));
            if((strcmp(Str, *Mini) >= 0) && (strcmp(Str, *Maxi) <= 0)) {
                StructTemp3 = Info_ATs(P);
                Cpt = Cpt + 1;
            }
            if(strcmp(Str, *Maxi) <= 0) {
                P = Fd_ATs(P);
            }
            else {
                P = NULL;
            }
        }
        else {
            Notempty = False;
        }
    }

    free(Str);
    return Cpt;
}

 void sim_word_search(char *file_name ,int m ,int n ,string2 A ,string2 B , string2 C){
    FILE *input1 , *input2 , *result;
    //array to temp store results for each simulation
    int temp[3][8];
    // statistics file
    result = fopen(file_name , "w");
    fprintf(result, "Sim;SearchType;BST0_EQXYZ;BST0_GTXYZ;BST0_LTXYZ;BST0_TOTAL;Triplet_EQXYZ;Triplet_GTXYZ;Triplet_LTXYZ;Triplet_TOTAL\n");

    /*repeat simulation m times*/
    for (int sim = 0; sim < m ; sim++)
    {
      /*reset the array to 0*/
      for ( int j = 0; j < 3; j++)
        for (int k = 0; k < 8 ; k++)
          temp[j][k] = 0 ;

      /*create 2 files of n rand words*/
      Genererfichier(input1,"input1.z",&A,&B,&C,n);
      Genererfichier(input2,"input2.z",&A,&B,&C,n);
      /*construct bst triplet and bst0*/
      Constructbst1(input1,"input1.z",&Bst1,&A,&B,&C);
      Constructbst2(input1,"input1.z",&Bst2,&A,&B,&C);
      Constructbst3(input1,"input1.z",&Bst3,&A,&B,&C);
      Constructbst0(input1,"input1.z",&Bst0);

      //traverse files and search for all the words
      get_sim_results(&input1,"input1.z", temp, A, B, C, Bst0);
      get_sim_results(&input2,"input2.z",temp, A, B, C, Bst0);

      //fill totals
      for (int i = 0; i <= 1; i++) {
        temp[i][3] = temp[i][0] + temp[i][1] + temp[i][2];
        temp[i][7] = temp[i][4] + temp[i][5] + temp[i][6];
      }

      for (int j = 0; j < 8; j++) {
          temp[2][j] = temp[0][j] + temp[1][j];
      }

      //write the results to stats file
      append_to_file(result,sim,temp);

      //display totals
      printf("\n---------------------------------[SIM %d] Nodes Visited Summary:------------------------------\n", sim);
      printf("  BST0    -> Successful: %d | Unsuccessful: %d | All: %d\n", temp[0][3], temp[1][3], temp[2][3]);
      printf("  Triplet -> Successful: %d | Unsuccessful: %d | All: %d\n", temp[0][7], temp[1][7], temp[2][7]);
    }
    fclose(result);
    printf("Detalied results in stats.txt\n");
}
  void append_to_file(FILE *output, int sim_number, int temp[3][8]) {
    const char* search_types[3] = { "Successful", "Unsuccessful", "All" };

    for (int i = 0; i < 3; i++) {
        fprintf(output, "%d;%s", sim_number, search_types[i]);

        // BST0_EQXYZ, BST0_GTXYZ, BST0_LTXYZ, BST0_TOTAL
        for (int j = 0; j <= 3; j++) {
            fprintf(output, ";%d", temp[i][j]);
        }

        // Triplet_EQXYZ, Triplet_GTXYZ, Triplet_LTXYZ, Triplet_TOTAL
        for (int j = 4; j <= 7; j++) {
            fprintf(output, ";%d", temp[i][j]);
        }
        fprintf(output, "\n");
    }
}



// search words in a given file and accumulate results in `temp`
void get_sim_results(FILE **fptr, char *file_name, int temp[3][8], string2 A, string2 B, string2 C, Pointeur_ATs Bst0) {
    Typestruct1_s S = malloc(sizeof(Typestruct1_s));
    S->Champ1 = malloc(255 * sizeof(char));
    string255 _Px1 = malloc(255 * sizeof(char));
    int Nodesnum;
    Pointeur_ATs P = NULL;
    Pointeur_ATs Par = NULL;

    Ouvrir_s(fptr, file_name, "A");

    while (!Finfich_s(*fptr)) {
        Lireseq_s(*fptr, S);
        strcpy(_Px1, Struct1_Ts(S));

        //search with triplet
        Nodesnum = 0;
        Recherche(&_Px1, &Par, &P, &Nodesnum, &A, &B, &C);
        if (P) //successful
        {
            if (!strcmp(Caract(_Px1, 1), A) || !strcmp(Caract(_Px1, 1), B) || !strcmp(Caract(_Px1, 1), C)) {
                temp[0][4] += Nodesnum;
            } else if (strcmp(Caract(_Px1, 1), A) > 0 || strcmp(Caract(_Px1, 1), B) > 0 || strcmp(Caract(_Px1, 1), C) > 0) {
                temp[0][5] += Nodesnum;
            } else {
                temp[0][6] += Nodesnum;
            }
        }
        else  //unsuccesful
        {
            if (!strcmp(Caract(_Px1, 1), A) || !strcmp(Caract(_Px1, 1), B) || !strcmp(Caract(_Px1, 1), C)) {
                temp[1][4] += Nodesnum;
            } else if (strcmp(Caract(_Px1, 1), A) > 0 || strcmp(Caract(_Px1, 1), B) > 0 || strcmp(Caract(_Px1, 1), C) > 0) {
                temp[1][5] += Nodesnum;
            } else {
                temp[1][6] += Nodesnum;
            }
        }

        //search in bst0
        Nodesnum = 0;
        Rechmotbst(&Bst0, &_Px1, &Par, &P, &Nodesnum);
        if (P) //successful
        {
            if (!strcmp(Caract(_Px1, 1), A) || !strcmp(Caract(_Px1, 1), B) || !strcmp(Caract(_Px1, 1), C)) {
                temp[0][0] += Nodesnum;
            } else if (strcmp(Caract(_Px1, 1), A) > 0 || strcmp(Caract(_Px1, 1), B) > 0 || strcmp(Caract(_Px1, 1), C) > 0) {
                temp[0][1] += Nodesnum;
            } else {
                temp[0][2] += Nodesnum;
            }
        }
        else  //unsuccesful
        {
            if (!strcmp(Caract(_Px1, 1), A) || !strcmp(Caract(_Px1, 1), B) || !strcmp(Caract(_Px1, 1), C)) {
                temp[1][0] += Nodesnum;
            } else if (strcmp(Caract(_Px1, 1), A) > 0 || strcmp(Caract(_Px1, 1), B) > 0 || strcmp(Caract(_Px1, 1), C) > 0) {
                temp[1][1] += Nodesnum;
            } else {
                temp[1][2] += Nodesnum;
            }
        }
    }

    Fermer_s(*fptr);
}

 /*--------------------------------------MAIN---------------------------------*/

int main(int argc, char *argv[])
{
    int option;
    FILE *output;

    srand(time(NULL));
    S = malloc(sizeof(Typestruct1_s));
    S->Champ1 = malloc(255 * sizeof(char));
    X = malloc(2 * sizeof(char));
    Y = malloc(2 * sizeof(char));
    Z = malloc(2 * sizeof(char));
    Str = malloc(255 * sizeof(char));

    system("cls");
    printf("\n========================================================\n");
    printf("Binary Search Tree Manager by Maram Daas and Hiba Khadir\n");
    printf("========================================================\n\n");

    printf("Entrez trois caracteres pour initialiser les arbres :\n");
    printf("Caractere X: "); scanf(" %s", X);
    printf("Caractere Y: "); scanf(" %s", Y);
    printf("Caractere Z: "); scanf(" %s", Z);

    int out = 0;
    while (!out)
    {
        system("cls");
        printf("============= MENU PRINCIPAL =============\n");
        printf("1 - Programme principal : modules de test\n");
        printf("2 - Simulation comparative (word-search)\n");
        printf("3 - Simulation comparative (rangequery)\n");
        printf("4 - Quitter\n");
        printf("==========================================\n");
        printf(">> Votre choix : ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\nInitialisation des fichiers et des arbres en cours...\n");
            Genererfichier(&Fich, "F2.z", &X, &Y, &Z, 100);
            Constructbst1(&Fich, "F2.z", &Bst1, &X, &Y, &Z);
            Constructbst3(&Fich, "F2.z", &Bst3, &X, &Y, &Z);
            Constructbst2(&Fich, "F2.z", &Bst2, &X, &Y, &Z);
            printf("Initialisation terminee avec succes !\n");
            printf("Appuyez sur ENTREE pour continuer...");
            getchar(); getchar();

            Quitter = 0;

            while (!Quitter)
            {
                system("cls");
                printf("\n==================== MENU ====================\n");
                printf("1. Parcours Inordre des arbres\n");
                printf("2. Compter les mots commencant par X / Y / Z\n");
                printf("3. Compter les mots par niveau\n");
                printf("4. Hauteur des arbres\n");
                printf("5. Recherche d'un mot\n");
                printf("6. Le RANGEQUERY\n");
                printf("7. Quitter\n");
                printf("==============================================\n");
                printf(">> Choisissez une option : ");
                scanf(" %d", &Choix);
                system("cls");

                switch (Choix)
                {
                case 1:
                    printf("\n--- Parcours Inordre du BST ---\n\n");
                    Inordre(&Bst1);
                    break;

                case 2:
                    printf("\n--- Comptage des mots commencant par X, Y ou Z ---\n\n");
                    Num = 0;
                    Comptespecial(&Bst1, &X, &Y, &Z, &Num);
                    printf("Total : %d\n", Num);
                    break;

                case 3:
                    printf("\n--- Comptage par niveau ---\n\n");
                    printf("--- BST1 ---\n"); Affich_niv(&Bst1, &X, &Y, &Z);
                    printf("\n--- BST2 ---\n"); Affich_niv(&Bst2, &X, &Y, &Z);
                    printf("\n--- BST3 ---\n"); Affich_niv(&Bst3, &X, &Y, &Z);
                    break;

                case 4:
                    printf("\n--- Hauteur des Arbres ---\n\n");
                    printf("BST1 : %d\n", Height(&Bst1));
                    printf("BST2 : %d\n", Height(&Bst2));
                    printf("BST3 : %d\n", Height(&Bst3));
                    break;

                case 5:
                    printf("\n--- Recherche d'un mot ---\n");
                    printf("Entrez un mot à rechercher : ");
                    scanf(" %[^\n]", Str);
                    Recherche(&Str, &Par, &P, &Num, &X, &Y, &Z);
                    printf("\nNoeuds visités : %d\n", Num);

                    if (P == NULL)
                        printf("[RESULTAT] Mot non trouvé.\n");
                    else {
                        printf("[RESULTAT] Mot trouvé : %s\n", Info_ATs(P)->Champ1);
                        if (Par != NULL)
                            printf("Parent : %s\n", Info_ATs(Par)->Champ1);
                    }
                    break;

                case 6:
                    printf("\n--- RANGEQUERY ---\n\n");
                    Rangequery_optimal(&Bst1, &Bst2, &Bst3, &X, &Y, &Z, &N);
                    break;

                case 7:
                    printf("\nMerci d'avoir utilisé notre gestionnaire BST ! À bientôt !\n");
                    Quitter = 1;
                    break;

                default:
                    printf("Option invalide. Veuillez réessayer.\n");
                }

                if (Choix != 7) {
                    printf("\nAppuyez sur ENTREE pour retourner au menu...");
                    getchar(); getchar();
                }
            }

            break;

        case 2:
            printf("\nCette operation prend du temps s'il vous plait ne sortez pas jusqu'on vous affiche le message de la fin\n");
            sim_word_search("stats.txt", 10, 10000, X, Y, Z);
            printf("\nFin, cliquez sur une touche pour revenir au menu principal\n");
            getchar(); getchar();
            break;

        case 3:
            {
                int range_option;
                printf("\n=============== SIMULATION RANGEQUERY ===============\n");
                printf("1 - Test rapide (1 execution)\n");
                printf("2 - Simulation complete (10 executions - ~15 minutes)\n");
                printf("=====================================================\n");
                printf(">> Votre choix : ");
                scanf("%d", &range_option);

                if (range_option == 1) {
                    printf("\nExecution du test rapide en cours...\n");
                    printf("Cette operation prend quelques seconds, veuillez patienter.\n\n");
                    sim_range_query_once("test_rangequery.txt", X, Y, Z);
                    printf("\nTest termine avec succes !\n");
                    printf("Les resultats sont sauvegardes dans le fichier 'test_rangequery.txt'\n");
                    printf("Vous pouvez ouvrir ce fichier avec un editeur de texte pour voir les statistiques.\n");
                } else if (range_option == 2) {
                    printf("\nExecution de la simulation complete en cours...\n");
                    printf("Cette operation prend environ 15 minutes maximum.\n");
                    printf("IMPORTANT: Ne fermez pas le programme pendant l'execution !\n");
                    printf("Veuillez patienter...\n\n");
                    sim_range_query_10("results_rangequery.txt", X, Y, Z);
                    printf("\nSimulation complete terminee avec succes !\n");
                    printf("Les resultats detailles sont sauvegardes dans le fichier 'results_rangequery.txt'\n");
                    printf("Ce fichier contient les statistiques de toutes les 10 executions.\n");
                } else {
                    printf("\nOption invalide. Retour au menu principal.\n");
                }

                printf("\nAppuyez sur ENTREE pour revenir au menu principal...");
                getchar(); getchar();
            }
            break;

        case 4:
            out = 1;
            break;

        default:
            printf("\nOption non existante. Veuillez réessayer.\n");
            printf("Appuyez sur ENTREE pour continuer...");
            getchar(); getchar();
        }
    }

    printf("\nLiberation de la memoire...\n");
    Libererarb(&Bst1);
    Libererarb(&Bst2);
    Libererarb(&Bst3);
    Libererarb(&Bst0);

    printf("Termine. Appuyez sur une touche pour revenir au menu principal.");
    system("PAUSE");
    return 0;
}
