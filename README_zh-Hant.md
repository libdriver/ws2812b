[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WS2812B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WS2812B是一個集控制電路與發光電路於一體的智能外控LED光源。其外型與一個5050LED燈珠相同，每個元件即為一個像素點。像素點內部包含了智能數字接口數據鎖存信號整形放大驅動電路，還包含有高精度的內部振盪器和可編程定電流控制部分，有效保證了像素點光的顏色高度一致。數據協議採用單線歸零碼的通訊方式，像素點在上電複位以後，DIN端接受從控制器傳輸過來的數據，首先送過來的24bit數據被第一個像素點提取後，送到像素點內部的數據鎖存器，剩餘的數據經過內部整形處理電路整形放大後通過DO端口開始轉發輸出給下一個級聯的像素點，每經過一個像素點的傳輸，信號減少24bit。像素點採用自動整形轉發技術，使得該像素點的級聯個數不受信號傳送的限制，僅受限信號傳輸速度要求。高達2KHz 的端口掃描頻率，在高清攝像頭的捕捉下都不會出現閃爍現象，非常適合高速移動產品的使用。 280μs以上的RESET時間，出現中斷也不會引起誤復位，可以支持更低頻率、價格便宜的MCU。 LED具有低電壓驅動、環保節能、亮度高、散射角度大、一致性好、超低功率及超長壽命等優點。將控制電路集成於LED上面，電路變得更加簡單，體積小，安裝更加簡便。

LibDriver WS2812B是LibDriver推出的WS2812B的全功能驅動，該驅動提供LED寫入等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example write](#example-write)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver WS2812B的源文件。

/interface目錄包含了LibDriver WS2812B與平台無關的SPI總線模板。

/test目錄包含了LibDriver WS2812B驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver WS2812B編程範例。

/doc目錄包含了LibDriver WS2812B離線文檔。

/datasheet目錄包含了WS2812B數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SPI總線模板，完成指定平台的SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ws2812b/index.html](https://www.libdriver.com/docs/ws2812b/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。