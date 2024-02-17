[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WS2812B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WS2812B는 제어 회로와 조명 회로를 통합한 지능형 외부 제어 LED 광원입니다. 외관은 5050LED 램프 비드와 동일하며 각 구성 요소는 픽셀입니다. 픽셀 내부에는 지능형 디지털 인터페이스 데이터 래치 신호 형성 및 증폭 구동 회로, 고정밀 내부 발진기 및 프로그래밍 가능한 정전류 제어 부품이 포함되어 있어 픽셀 조명의 색상이 매우 일정하게 유지되도록 합니다. 데이터 프로토콜은 단일 라인 제로 코드 통신 방식을 채택합니다.픽셀 전원을 켜고 재설정한 후 DIN 터미널은 컨트롤러에서 전송된 데이터를 수락합니다.먼저 전송된 24비트 데이터는 첫 번째 픽셀에서 추출하여 전송됩니다. 나머지 데이터는 내부 성형 처리 회로에 의해 성형 및 증폭된 후 DO 포트를 통해 다음 계단식 픽셀로 전달 및 출력됩니다. 한 픽셀 전송 후 신호는 24비트 감소합니다. 픽셀은 자동 성형 및 전달 기술을 채택하여 픽셀의 계단식 수는 신호 전송에 의해 제한되지 않고 신호 전송 속도 요구 사항에 의해서만 제한됩니다. 최대 2KHz의 포트 스캐닝 주파수는 고화질 카메라 캡처 시 깜박이지 않으므로 고속 모바일 제품 사용에 매우 적합합니다. 280μs 이상의 RESET 시간은 인터럽트가 발생하더라도 False Reset을 일으키지 않으며, 저주파수 및 저렴한 MCU를 지원할 수 있다. LED는 저전압 구동, 환경 보호 및 에너지 절약, 고휘도, 큰 산란 각도, 우수한 일관성, 저전력 및 긴 수명의 장점이 있습니다. LED에 제어 회로를 통합함으로써 회로가 단순해지고 부피가 작아지며 설치가 더 쉽습니다.

LibDriver WS2812B는 LibDriver에서 출시한 ws2812b의 전체 기능 드라이버입니다. WS2812B는 led 쓰기 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example write](#example-write)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver WS2812B의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver WS2812B용 플랫폼 독립적인 SPI 버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver WS2812B 드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver WS2812B 프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver WS2812B 오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 WS2812B 데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 SPI 버스 템플릿을 참조하여 지정된 플랫폼에 대한 SPI 버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/ws2812b/index.html](https://www.libdriver.com/docs/ws2812b/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.