//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ****************************** TEST **************************** //	Version testée et validée.
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme test regroupant les fonctions nécessaires, pour 		*/
/*   l'utilisation du module DTMF, avec un arduino MEGA.			*/
/*   Shield LCD_Keypad												*/
/* **************************************************************** */
/*  Le montage détecteur des valeurs par DTMF, qu'il stock sous		*/
/*	forme de chaine, composée au max de 12 valeurs ou d'une durée   */
/*	de réception inferieur à 10secondes(Tmax).					   	*/
/*	La chaine est ensuite envoyé sur le port Serie.				   	*/
/*																	*/
/* **************************************************************** */
/*  Version: alpha				---				Date: 08/11/2014	*/	
/*  OctoGeeK					---				Octo Don Julo		*/	
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
#include <LiquidCrystal.h>											// Inclusion de la Bibliothèque qui permet de gérer un écran lcd. (ici 2x16)
#include <Timer.h>													// Inclusion de la Bibliothèque d'horloge. 
#include <DTMF.h>													// Inclusion de la Bibliothèque pour la conversion DTMF.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********** Constantes, Variables, Fonctions Internes *********** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	---		---			Variables Comm-Serie			---		--- //
	int BaudCOM1				= 9600;								// Vitesse de communication serie : 9600, etc, 19200, 57600, 19200, 115200.
// 	---		---				Variables Timer				---		--- //
	Timer horloge;													// Initialisation d'un timer. 
	#define Tmax				11									// Valeur max du compteur de durée de validation reception.
//////////////////////////////////////////////////////////////////////
// ************************ Shield LCD keypad ********************* //
//////////////////////////////////////////////////////////////////////
// 	---		---		Constantes brochages LCD 2x16		---		--- //	
	#define LCD_D4      			4								// Definition des broches LCD du Shield LCD Keypad.
	#define LCD_D5      			5
	#define LCD_D6      			6
	#define LCD_D7      			7
	#define LCD_RS     				8
	#define LCD_EN      			9

	#define boutonRIGHT  			0								// Definition des boutons du Shield LCD Keypad.
	#define boutonUP     			1
	#define boutonDOWN   			2
	#define boutonLEFT   			3
	#define boutonSELECT 			4
	#define boutonNONE   			5
	LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);	// Brochage du LCD.
// 	---				Variables des 5 boutons poussoirs			--- //	
	int LcdBouton  	= 0;
	int read_LCD_boutons()
	{
		LcdBouton = analogRead(0);    								// Lecture analogique de la valeur sur broche A0
		// For LCD keypad shield V1.0 :
		if (LcdBouton > 1000) return boutonNONE;
		if (LcdBouton < 50)   return boutonRIGHT;  
		if (LcdBouton < 195)  return boutonUP; 
		if (LcdBouton < 380)  return boutonDOWN; 
		if (LcdBouton < 555)  return boutonLEFT; 
		if (LcdBouton < 790)  return boutonSELECT;   
		return boutonNONE;  										// Quand aucuns boutons n'est utilisé 
	}
//////////////////////////////////////////////////////////////////////
// ********************** Module DTMF DFrobot ********************* //
//////////////////////////////////////////////////////////////////////
// 	---		---		Constantes brochages module DTMF	---		--- //
	#define DTMF_B1      			38								// LSD								
	#define DTMF_B2      			36								// --- message binaire
	#define DTMF_B4      			34								// --- DTMF
	#define DTMF_B8      			32								// MSB
	#define DTMF_Str     			30								// Bit Strobe (a 1 si DTMF detecté)
// 	---		---			Variables Decodeur DTMF			---		--- //
	int DTMF_MES 					= 0;							// Message DTMF decimal.
	char DTMF1 						[14];							// Permet le stockage des octets DTMF sous forme de numero. 14 chiffres Max.
	int Count 						= 0;							// Variable pour compteur.
	int Valide 						= 0;							// Variable pour la validation de la reception d'un message (s'incrémente).
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup() 
{
// --- 		Initialisation du module DTMF.		---	//
	pinMode(DTMF_B1, INPUT); 										// bit 1, pin 11 du CM8870.
	pinMode(DTMF_B2, INPUT); 										// bit 2, pin 12 du CM8870.
	pinMode(DTMF_B4, INPUT); 										// bit 4, pin 13 du CM8870.
	pinMode(DTMF_B8, INPUT); 										// bit 8, pin 14 du CM8870.
	pinMode(DTMF_Str, INPUT); 										// Strobe, pin 15 du CM8870.
// --- 		Initialisation  Serie.				---	//	
	Serial.begin(BaudCOM1);												// Initialise la vitesse de connexion série.	
	Serial.println(" Octo-TEST DTMF Va"); 									// Support : affichage serie	
// --- 		Initialisation shield LCD Keypad.	---	//
	lcd.begin(16, 2);												// Initialise le LCD avec le nb de caractere et le nb de ligne.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
	lcd.print("    Octo-GeeK   ");	 								// Ecrie le message sur le LCD.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
	lcd.print("  TEST DTMF Va  ");	 								// Ecrie le message sur le LCD.
	delay(2000);													// Temporise.
	lcd.clear();													// RAZ du LCD.			
// --- 			Initialisation du Timer. 		---// 
	horloge.every (940, compteur);									// Appele du programme "compteur" toute les secondes environ.

	Serial.println("debut du programme.");									// Support : affichage serie.
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop() 
{
	horloge.update();												// incrémente le timer.
// --- 				Fonctionnement du module DTMF.				---	//
	if (digitalRead(DTMF_Str) == HIGH)								// Si le bit de détection DTMF passe à 1.			
	{
		DetectDTMF();												// Appel du sous-programme de detection de caractere DTMF.
		miseenformemessage();										// Appel du sous-programme de mise en forme du message.
	}
	if(Valide >= Tmax)												// Si le timer est terminé.
	{		DTMFserie();		}									// Appele le sous-programme DTMFserie.	
}

//////////////////////////////////////////////////////////////////////	OK
// ************************* Décodeur DTMF ************************ //
//////////////////////////////////////////////////////////////////////
void DetectDTMF() 													// Détection et décodage DTMF.
{	
	if (Valide == 0)												// Si aucun message n'a etait recu depuis Tmax.
	{		Valide = 1;					}
	Serial.print(" Bits dtmf recu : "); 									// Support : affichage serie. 
	if (digitalRead(DTMF_B1) == HIGH)								// Met a 1 si le bit 1 est détecté. ou pas.
	{ 		DTMF_MES = 1;  				} 
	else 
	{ 		DTMF_MES = 0;  				} 
	if (digitalRead(DTMF_B2) == HIGH)								// Ajoute 2 si le bit 2 est détecté. ou pas.
	{		DTMF_MES = DTMF_MES + 2;  	} 
	if (digitalRead(DTMF_B4) == HIGH)								// Ajoute 4 si le bit 4 est détecté. ou pas.
	{ 		DTMF_MES = DTMF_MES + 4;  	} 
	if (digitalRead(DTMF_B8) == HIGH)								// Ajoute 8 si le bit 8 est détecté. ou pas.
	{ 		DTMF_MES = DTMF_MES + 8;  	}
	Serial.println(DTMF_MES);												// Support : affichage serie du nombre recu.
	lcd.print(DTMF_MES);											// Affichage LCD du nombre recu.
	delay(200);
}
//////////////////////////////////////////////////////////////////////	OK
// ******************* Compteur de message DTMF ******************* //
//////////////////////////////////////////////////////////////////////
void compteur ()													// Incrémente une valeur si elle n'est pas nul toutes les secondes.
{
	if (Valide !=0)
	{		Valide++;		}
}
//////////////////////////////////////////////////////////////////////	OK
// ***************** Mise en forme du message DTMF **************** //
//////////////////////////////////////////////////////////////////////
void miseenformemessage()											// Sous programme stockant le message DTMF dans un tableau
{
	if(DTMF_MES==10)												// 0
	{	DTMF_MES = 48;			}									// ascii 48
	else if(DTMF_MES==11)											// * 
	{	DTMF_MES = 42;			}									// ascii 42
	else if(DTMF_MES==12)											// #
	{	DTMF_MES = 35;			}									// ascii 35
	else
	{	DTMF_MES = DTMF_MES+48;	}									// Ajoute 48 pour la convertion ascii.
	DTMF1 [Count] = DTMF_MES;										// Ajoute la valeur recu dans le tableau.	
	if(Count < 13)//13?												// Si le compteur est inferieur à la derniere cellule du tableau.
	{	Count ++;				}									// Incemente le compteur.
	if(Count == 13)//13?											// Si le compteur est égal à la derniere cellule du tableau.
	{	DTMFserie();			}									// Appele le sous-programme DTMFserie.
}
//////////////////////////////////////////////////////////////////////	OK
// ******************** Message DTMF Sur Serie ******************** //
//////////////////////////////////////////////////////////////////////
void DTMFserie()													// Sous programme stockant le message DTMF dans un tableau
{
	Serial.print(" Message recu : ");								// Support : affichage serie du nombre recu.
	Serial.println(DTMF1);											// Support : affichage serie du nombre recu.
	Count			= 0;											// Reinitialise le comptage des chiffres recus à 0.
	Valide			= 0;											// Reinitialise le comptage du temps valide à 0.
	for(int i=0;i<13;i++)											// Reinitialise le message DTMF à 0.
    {DTMF1[i] = 0;}
}
////////////////////////////////////////////////////////////////////// FIN