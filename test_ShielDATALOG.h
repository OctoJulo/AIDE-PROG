//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ****************************** TEST **************************** //	Version testée et validée.(sauf la synchro RTC)
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme test regroupant les fonctions nécessaires, pour 		*/
/*   l'utilisation du Shield datalog, avec un arduino MEGA.			*/
/*																	*/
/* **************************************************************** */
/*  Le montage crée un fichier horodatée à la racine de la SD.		*/
/*	Le fichier comporte une entète et la date et heure de création. */
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
// 	---		---				Variables SD				---		--- //
	File fichier;													// Crée un objet fichier.
	File racine;													// Crée un objet racine.
    char nomfichier				[8];								// Permet le stockage du nom du fichier avec horodatage.
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
	Serial.println(" Octo-TEST Datalog Va"); 								// Support : affichage serie	
// --- 		Initialisation du shield datalog.	---	//
	pinMode(53, OUTPUT);
    Wire.begin();													// Initialisation de la fonction I2C.
    RTC.begin();													// Initialisation de la fonction RTC.
	SynchroPCtoRTC ();												// Appel du sous-programme de synchronisation du DS1307 par le port serie (logiciel).
// --- 		Initialisation SD et fichier.		---	//
	designationfichier(); 											// Appel du sous-programme créant le nom du fichier.
	SDInit();														// Appel du sous-programme créant le fichier.
	Serial.println("debut du programme.");									// Support : affichage serie.
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop() 
{

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

//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Programme SD ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////	OK
// *********************** Initialisation SD ********************** //
//////////////////////////////////////////////////////////////////////
void SDInit() 														// Initialise la création du fichier sur la carte SD.
{
	if (!SD.begin(10,11,12,13))										// Si l'initialisation n'a pas eu lieu.
	{
		Serial.println("initialisation SD ratee!");							// Support: affichage serie.
		return;														// Sort de la boucle.
	}
	Serial.println("initialisation ok.");									// Support: affichage serie.
// 	--- fichier horodaté
	if (SD.exists(nomfichier)) 										// Si le fichier est presen sur la carte SD.
	{
		Serial.print(nomfichier);											// Support: affichage serie.
		Serial.println(" deja present.");									// Support: affichage serie.
		SDreboot();													// Appele le sous-programme d'indication du reboot.
	}
	else 
	{
		fichier = SD.open(nomfichier, FILE_WRITE);					// Crée le fichier uniquement si il n'existe pas.
		Serial.print("Creation du fichier : ");								// Support : affichage serie.
		Serial.println(nomfichier);											// Support : affichage serie.
		fichier.println("//-- OctoGeeK - Test Datalog Va --//");	// Entête.
		//fichier.println(LaDate);									// nom du fichier.
		fichier.println("------------------------------------");// Séparateur entête.
		fichier.close();											// Ferme le fichier.
	}
}
//////////////////////////////////////////////////////////////////////	OK
// *********************** Reboot fichier SD ********************** //
//////////////////////////////////////////////////////////////////////
void SDreboot()														// Ecrie dans le programme la date et l'heure du reboot.
{
	fichier = SD.open(nomfichier, FILE_WRITE); 						// Ouvre le fichier en écriture.
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();									// Variable des années.
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);
	fichier.print("Reboot : ");										// Ecrie "reboot" dans le fichier.
	fichier.println(LaDate);										// Ecrie l'horodatage. 
	fichier.close();												// Ferme le fichier.
}
//////////////////////////////////////////////////////////////////////	OK
// *********************** Nom du fichier SD ********************** //
//////////////////////////////////////////////////////////////////////
void designationfichier() 											// Crée une chaine de caractère pour le nom du fichier.	// Format: MMJJTEST.txt
{
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	sprintf(nomfichier,"%02d%02dTEST.txt",mois,jour);				//
}
