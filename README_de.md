[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WS2812B
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

WS2812B ist eine intelligente Steuer-LED-Lichtquelle, bei der die Steuerschaltung und der RGB-Chip in einem Paket von 5050-Komponenten integriert sind. Sie enthält intern einen intelligenten digitalen Port-Datenlatch und eine Signalumformungs-Verstärkungstreiberschaltung. Enthält auch einen präzisen internen Oszillator und eine spannungsprogrammierbare Konstante Stromsteuerteil, wodurch die Lichtfarbe der Pixelpunkte effektiv sichergestellt wird. Das Datenübertragungsprotokoll verwendet einen einzelnen NZR-Kommunikationsmodus. Nach dem Zurücksetzen des Pixels beim Einschalten empfängt der DIN-Anschluss Daten vom Controller, das erste Pixel sammelt anfängliche 24-Bit-Daten, die dann an das interne Datenlatch gesendet werden, die anderen Daten, die
Umformung durch die interne Signalumformungs-Verstärkungsschaltung, die durch den DO-Anschluss an das nächste Kaskadenpixel gesendet wird. Nach der Übertragung wird für jeden Pixel das Signal auf 24bit reduziert. Pixel übernehmen die automatische Umformungsübertragungstechnologie, wodurch die Pixelkaskadenzahl nicht auf die Signalübertragung beschränkt ist, sondern nur von der Geschwindigkeit der Signalübertragung abhängt. RESET-Zeit> 280 μs, es verursacht kein falsches Zurücksetzen während der Unterbrechung, es unterstützt die niedrigere Frequenz und ist kostengünstig MCU.Refresh-Frequenz-Updates auf 2 kHz, niedrige Bildfrequenz und kein Flimmern erscheinen in der HD-Videokamera, es verbessert den hervorragenden Anzeigeeffekt. LED mit niedriger Betriebsspannung, Umweltschutz und Energieeinsparung, hohe Helligkeit, Streuwinkel ist groß, gute Konsistenz, niedrig Leistung, lange Lebensdauer und andere Vorteile. Der oben in die LED integrierte Steuerchip wird zu einer einfacheren Schaltung, einem geringen Volumen und einer bequemen Installation.

LibDriver WS2812B ist der voll funktionsfähige Treiber von ws2812b, der von LibDriver gestartet wurde. WS2812B bietet LED-Schreiben und andere Funktionen. LibDriver entspricht MISRA.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example write](#example-write)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver WS2812B-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver WS2812B SPI.

/test enthält den Testcode des LibDriver WS2812B-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver WS2812B-Beispielcode.

/doc enthält das LibDriver WS2812B-Offlinedokument.

/Datenblatt enthält WS2812B-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example write

```C
#include "driver_ws2812b_basic.h"

uint8_t res;
uint32_t i;
static uint32_t gs_rgb[21]; 
static uint8_t gs_temp[1024];

/* init */
res = ws2812b_basic_init();
if (res != 0)
{
    return 1;
}

/* write color */
for (i = 0; i < 21; i++)
{
    gs_rgb[i] = color;
}

/* write data */
res = ws2812b_basic_write(gs_rgb, 21, gs_temp, 1024);
if (res != 0)
{
    (void)ws2812b_basic_deinit();

    return 1;
}

/* close the chip */
res = ws2812b_basic_deinit();
if (res != 0)
{
    return 1;
}
else
{
    return 0;
}
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ws2812b/index.html](https://www.libdriver.com/docs/ws2812b/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.