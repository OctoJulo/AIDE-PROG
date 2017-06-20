//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ****************************** TEST **************************** //	Version a testée et a validée.
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme test regroupant les fonctions nécessaires, pour 		*/
/*   l'utilisation du Shield datalog, avec un arduino MEGA.			*/
/*   Shield LCD_Keypad												*/
/* **************************************************************** */
/*  Le montage Affiche sur le LCD la date et l'heure retourné par	*/
/*	le DS1307 du shield datalog										*/
/*  Le montage peut aussi synchroniser le DS1307 du shield avec     */
/*	un ordinateur par le port serie par l'utilisation d'un logiciel.*/ 
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
#include <Wire.h>													// Inclusion de la Bibliothèque Wire pour la gestion de l'I2C.
#include <SPI.h>													// Inclusion de la Bibliothèque pour la communication SPI.		// necessaire pour la bibliothque SD.
#include <SD.h>														// Inclusion de la Bibliothèque pour l'utilisation des modules SD. Représentant la carte mémoire SD.
#include <RTClib.h>													// Inclusion de la Bibliothèque Pour le module Temps-réel.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********** Constantes, Variables, Fonctions Internes *********** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	---		---			Variables Comm-Serie			---		--- //
	int BaudCOM1				= 9600;								// Vitesse de communication serie : 9600, etc, 19200, 57600, 19200, 115200.
	int octetReception			= 0; 								// Variable de stockage des valeurs reçues sur le port Série. (ASCII)
	char caractereRecu			= 0; 								// Variable pour stockage caractère recu.
	int compt					= 0; 								// Variable comptage caractères reçus.
	String chaineReception		= ""; 								// Déclare un objet String vide pour reception chaine.
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
// ********************** Shield Datalogging ********************** //
//////////////////////////////////////////////////////////////////////
// 	--- Le Shield dispose d'un lecteur SD et d'un RTC DS1307.
// 	--- Pour l'utilisation sur un Mega, utilisée la bibliothque SC(adafruit mega).
	#define brocheSDCardSelect		4	 							// broche utilisée pour sélectionner la SD card	(4,8,10)
	#define brocheSDchipSelect		53								// Met la broche(SS)  à 10 (UNO) ou 53 (MEGA) en sortie // Nécessaire avec shield ethernet. 
// change this to match your SD shield or module;
//     Arduino Ethernet shield: pin 4
//     Adafruit SD shields and modules: pin 10
//     Sparkfun SD shield: pin 8
	const int chipSelect = 10;	
// 	--- 	---					RTC						---		--- //
	RTC_DS1307 RTC; 

// 	---		---			Variables Horodatage			---		--- //
	int secondes;  													// Variable des secondes.
	int minutes;  													// Variable des minutes.
	int heures; 													// Variable des heures.
	int joursemaine; 												// Variable du jour de la semaine.
	int jour;  														// Variable du jour du mois.
	int mois;  														// Variable des mois.
	int annee; 														// Variable des années.
	char LaDate					[22]; 								// Variable regroupant la date et l'heure.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup() 
{
// --- 		Initialisation  Serie.				---	//	
	Serial.begin(BaudCOM1);											// Initialise la vitesse de connexion série.	
	Serial.println(" Octo-TEST Horloge Va"); 								// Support : affichage serie	
// --- 		Initialisation du shield datalog.	---	//
	pinMode(53, OUTPUT);
    Wire.begin();													// Initialisation de la fonction I2C.
    RTC.begin();													// Initialisation de la fonction RTC.
	SynchroPCtoRTC ();												// Appel du sous-programme de synchronisation du DS1307 par le port serie (logiciel).

// --- 		Initialisation shield LCD Keypad.	---	//
	lcd.begin(16, 2);												// Initialise le LCD avec le nb de caractere et le nb de ligne.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
	lcd.print("    Octo-GeeK   ");	 								// Ecrie le message sur le LCD.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
	lcd.print(" Octo-Horloge Va");	 								// Ecrie le message sur le LCD.
	delay(2000);													// Temporise.
	lcd.clear();													// RAZ du LCD.	
	
	Serial.println("debut du programme.");									// Support : affichage serie.
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop() 
{
	AffidateLCD ();													// Appel du sous-programme de visualisation LCD de la date et l'heure. 
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Programme RTC ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////	NOK
// ***************** Synchronisation du DS1307  ******************* //
//////////////////////////////////////////////////////////////////////
void SynchroPCtoRTC()												// Affiche la date et l'heure sur l'ecran LCD.
{	
	Serial.println('A'); 											// Envoi un "top" au programme de mise à l'heure.
	while (millis()<5000) 											// Attente 5 secondes la liaison série.
	{
		while (Serial.available()>0) 								// Tant qu'un octet est dans la liaison série.
		{ 
			octetReception=Serial.read(); 							// Lit le 1er octet reçu et le met dans la Variable .     
			if (octetReception==13)  								// Si l'octet reçu est un retour chariot(CR ou 13).
			{
			// 	---		Converti la chaine en entier pour les valeurs de temps
				secondes = int((chaineReception.charAt(0)-48)*10)+int(chaineReception.charAt(1)-48) ;
				minutes = int((chaineReception.charAt(2)-48)*10)+int(chaineReception.charAt(3)-48);
				heures = int((chaineReception.charAt(4)-48)*10)+int(chaineReception.charAt(5)-48);
				joursemaine = 1;
				jour = int((chaineReception.charAt(6)-48)*10)+int(chaineReception.charAt(7)-48);
				mois = int((chaineReception.charAt(8)-48)*10)+int(chaineReception.charAt(9)-48);
				annee = int((chaineReception.charAt(12)-48)*10)+int(chaineReception.charAt(13)-48);			
				RTC.adjust(DateTime(annee, mois, jour, heures, minutes, secondes)); 		
				Serial.println("RTC finito");								// Support : affichage serie.
				chaineReception=""; 								// RAZ de la chaine de réception.
				break; 												// Sort de la boucle while.
			}
			else 													// Si le caractère reçu n'est pas un saut de ligne.
			{ 
				caractereRecu = char(octetReception); 				// Convertit l'octet reçu en caractère.
				chaineReception = chaineReception + caractereRecu; 	// Ajoute le caratère à la chaine.
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////	OK
// ********************** Affichage horodaté  ********************* //
////////////////////////////////////////////////////////////////////// N'appele pas de sous programme, usilise LiquidCrystal.h et RTClib.h
void AffidateLCD () 												// Affiche la date et l'heure sur l'ecran LCD.
{		
	DateTime now = RTC.now();										// Déclare la fonction retournant l'horodatage.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD.
	lcd.print(now.day(), DEC);										// Affiche sur le LCD, le jour.
    lcd.print('/');													// Affiche sur le LCD, le separateur.
    lcd.print(now.month(), DEC);									// Affiche sur le LCD, le mois.	
    lcd.print('/');													// Affiche sur le LCD, le separateur.
	lcd.print(now.year(), DEC);										// Affiche sur le LCD, l'année.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD.
    lcd.print(now.hour(), DEC);										// Affiche sur le LCD, l'heure.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.minute(), DEC);									// Affiche sur le LCD, les minutes.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.second(), DEC);									// Affiche sur le LCD, les secondes.
    lcd.print(' ');													// Affiche sur le LCD.	
}