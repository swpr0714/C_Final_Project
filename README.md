# 112-2 C程式語言 期末專題 - 線上撲克牌遊戲
<!-- PROJECT SHIELDS -->

![Win][win11-shield]
![VSCode][vs-code]
![VS][vs-shield]
![C][c-shield]
![CMAKE][cmake-shield]  
[![MIT License][license-shield]][license-url]
[![Contributors][contributors-shield]][contributors-url]
[![Commit][commit-shield]][commit-url]
![Build][build-shield]
![Test][test-shield]
<!-- [![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url] -->

## 目錄

- [112-2 C程式語言 期末專題](#112-2-c程式語言-期末專題-1)
      - [題目：線上撲克牌遊戲](#題目線上撲克牌遊戲-1)
  - [目錄](#目錄)  
  - [組員名單](#組員名單)
  - [程式介紹與安裝](#程式介紹與安裝)
  - [遊戲規則](#遊戲規則)
    - [系統配置要求](#系統配置要求)
    - [文件目錄說明](#文件目錄說明)
    - [建置](#建置)
    - [版本控制](#版本控制)
  - [作者](#作者)
  - [版權說明](#版權說明)
  - [銘謝](#銘謝)

## 組員名單
#### 1. B10803144 嚴和楷
#### 2. B11131005 黃宇
#### 3. B11131016 鄧盛文
## 程式介紹與安裝
#### 這是一個基於TCP架構，由兩個玩家進行的大老二遊戲，這個遊戲是由兩個`Client`與一個`Server`所構成。首先，先從Github下載[Release版][Release]的程式，由一台電腦執行`Server.exe`，隨後由另外兩台電腦執行`Client.exe`並同時傳入Server的IPV4位址，方法如下：
##### Server 查看IPV4位址 
```bash
ipconfig /all
```
##### Server 啟動`Server.exe`
```bash
.\Server.exe
```
##### Client 啟動`Client.exe`並傳入Server IP 
```bash
.\Client.exe 192.168.0.1
```
##### 若Client啟動未傳入IP則預設為使用LOCALHOST ( 172.0.0.1 ) 進行通訊
## 遊戲規則
#### 由伺服器隨機將不含鬼牌的牌組分送給兩位玩家，由取得梅花三( Clever 3 )的玩家先行出牌，該玩家可選擇：
**1. Single ( 單張 )**  
**2. Pair ( 對子 )**  
**3. Straight ( 順子 )**  
**4. Full House ( 葫蘆 )**  
**5. Four of a Kind ( 鐵支 )**  
**6. Flush ( 同花順 )**  
#### 總共六種牌型，並按照所選牌型出牌。若判斷為合法出牌，傳入伺服器後，便會傳送給另一位玩家，另一位玩家需出同牌型更大的牌或是選擇PASS，若選擇出牌則持續此循環直至有一方選擇PASS，若選擇PASS則另一位玩家可重新選擇出牌的牌型。持續此循環直至其中一方出完所有手牌，則該方獲勝，程式停止。


## 系統配置要求

#### 1. 作業系統：Windows 11
#### 2. 開發環境：
  1. Visual Studio ( CL編譯器 )
  2. Visual Studio Code 或其他編輯器
  3. CMake

## **安装步骤**

#### 1. Clone the repository

```bash
git clone https://github.com/swpr0714/C_Final_Project.git
```

## 文件目錄說明
```
File Tree
├── bin/
│   ├── Client.exe
│   ├── Server.exe
│       
├── /build/
│   ├── makefile
│       
├── /header/
│   ├── client_func.h
│   ├── com_setup.h
│   ├── poker.h
│   ├── server_func.h
│       
├── /lib/
│   ├── advapi32.dll
│   ├── mswsock.dll
│   ├── ws2_32.dll
│
└── /src/
│   ├── Client.c
│   ├── client_func.c
│   ├── com_setup.c
│   ├── poker.c
│   ├── Server.c
│   ├── server_func.c
│
├── .gitignore
├── LICENSE
├── README.md   
```

### 建置
先從Github Clone此專案的原始碼
```Bash
git clone htts://github.com/swpr0714/C_Final_Project.git
```
在cmd中進入`.\build`資料夾，使用`makefile`進行建置。[makefile詳細內容請見此處][makefile-url]
```bash
cd .\build
make All
```

### 版本控制

此專案使用Git進行版本控制。您可以在Repository參看目前可用版本。

### 作者

**鄧盛文**  
Github: https://github.com/swpr0714  
Mail: swpr0714@gmail.com

### 版權說明

此項目簽署 MIT 授權，詳細內容請參考 [LICENSE](https://github.com/swpr0714/C_Final_Project/blob/main/LICENSE)

### 銘謝
- [Img Shields](https://shields.io)
- [Johnny20tech](https://github.com/johnny20tech)

<!-- links -->
[your-project-path]:shaojintian/Best_README_template
[contributors-shield]: https://img.shields.io/github/contributors/swpr0714/C_Final_Project.svg?style=flat-square
[contributors-url]: https://github.com/swpr0714/C_Final_Project/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/shaojintian/Best_README_template.svg?style=flat-square
[forks-url]: https://github.com/shaojintian/Best_README_template/network/members
[stars-shield]: https://img.shields.io/github/stars/shaojintian/Best_README_template.svg?style=flat-square
[stars-url]: https://github.com/shaojintian/Best_README_template/stargazers
[issues-shield]: https://img.shields.io/github/issues/shaojintian/Best_README_template.svg?style=flat-square
[issues-url]: https://img.shields.io/github/issues/shaojintian/Best_README_template.svg?style=flat-square
[commit-shield]: https://img.shields.io/github/commit-activity/m/swpr0714/C_Final_Project?style=flat-square
[commit-url]:https://github.com/swpr0714/C_Final_Project/commits
[build-shield]:https://img.shields.io/badge/build-passing-brightgreen?style=flat-square
[test-shield]: https://img.shields.io/badge/test-passing-brightgreen?style=flat-square

[license-shield]: https://img.shields.io/github/license/swpr0714/C_Final_Project?style=flat-square
[license-url]: https://github.com/swpr0714/C_Final_Project/blob/main/LICENSE
[vs-code]: https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=flat-square&logo=visual%20studio%20code&logoColor=white
[vs-shield]:https://img.shields.io/badge/Visual_Studio-5C2D91?style=flat-square&logo=visual%20studio%20code&logoColor=white
[c-shield]:https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white
[cmake-shield]:https://img.shields.io/badge/CMake-064F8C?style=flat-square&logo=cmake&logoColor=white
[win11-shield]:https://img.shields.io/badge/Windows_11-0078d4?style=flat-square&logo=windows-11&logoColor=white
[makefile-url]:https://github.com/swpr0714/C_Final_Project/blob/main/build/makefile
[Release]: https://github.com/swpr0714/C_Final_Project/releases/tag/Release
