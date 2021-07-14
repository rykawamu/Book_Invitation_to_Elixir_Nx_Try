= Nxってなんだろう

さて、Nxとはなんでしょうか？

本章では、Nxについて簡単に説明します。

== Nxとは

Nxとは、関数型プログラミング言語Elixir用の@<b>{テンソル計算用ライブラリ}@<fn>{nx_descr}@<fn>{cpugpu}です。

「@<b>{N}umerical Eli@<b>{x}ir」から命名されています。

呼び方は「@<b>{エヌエックス}」が一般的です。

ロゴには、一見するとリスにも見えるマスコットキャラ「@<b>{ヌンバット}」が描かれています。

//indepimage[numbat_01][Nxのロゴ（GitHub公式ページより拝借）][scale=0.4]{
//}


//footnote[nx_descr][公式ページでは、「Multi-dimensional arrays (tensors) and numerical definitions for Elixir」と紹介されています。]
//footnote[cpugpu][本書では解説しませんがCPU/GPUに対してマルチステージコンパイルが可能です。]

Nxは、GitHub上で公開されている@<fn>{nx_github}オープンソースです。

//footnote[nx_github][@<href>{https://github.com/elixir-nx/nx}]

Nxのリポジトリには、Nxの他にも「@<b>{EXLA}@<fn>{exla}」「@<b>{Torchx}@<fn>{torchx}」というライブラリも含まれています。ただし、その2つは本書では紹介しません。

//footnote[exla][GoogleのXLA（Accelerated Linear Algebra）用のElixirクライアント。NxをCPU/GPU/TPU向けにコンパイルするためのNxライブラリも含まれています。]
//footnote[torchx][LibTorch用のElixirクライアント。]

　

テンソル計算用ライブラリとは、文字通り"@<b>{テンソル}"を取り扱って計算するライブラリです。
テンソルとは、「@<b>{ベクトルや行列を一般化したもの}」@<fn>{tensor}を指します。
数学では、@<b>{スカラー}は0次元配列、@<b>{ベクトル}は1次元配列、@<b>{行列}は2次元配列を指します。
そして、3次元配列以上の多次元配列が一般的にテンソルという扱いです。

ただし、本書では話を単純化するために、ベクトルや行列も含めたN次元の配列をテンソルと呼びます。

//footnote[tensor][実際はもっと詳しい定義があります。詳細はWikipediaなどを参照してください。]

多次元配列の例を1つあげます。行列（2次元配列）は、以下のように表現します。

//blankline

@<m>{\begin{bmatrix\} a & b & c \\\\ d & e & f \\\\ \end{bmatrix\}}

//blankline

Nxは、Elixirの作者である@<b>{José Valim}氏の肝いりプロジェクトです。
Elixirを動かすために必要な@<b>{Erlang}@<fn>{erlang}にプルリクエストを投げ、Nxが性能を出せるようにしたという程の力の入れよう@<fn>{nx_version}です。
言語の作者本人が作成しているので、ライブラリのフォローなどの保証は十分にあると考えて良いでしょう。

　

次の章では、Nxを利用して、実際にテンソルの計算をしてみましょう。

//footnote[erlang][「アーラン」と呼びます。ElixirはErlang VM上で動くプログラム言語です。]

//footnote[nx_version][ただし、これによってNxを動かすためのバージョン指定は厳しくなりました。]

===[column] コラム：Nxのマスコット「ヌンバット」

Nxのプロジェクトのマスコットは「Numbat（ヌンバット）」と呼ばれる動物です。
一見するとリスのようですが、和名だと「フクロアリクイ」と呼ばれています。

ヌンバットは、オーストラリア南部原産の有袋類です。
絶滅の危機（推定1000頭以下）に瀕しており、募金が集められています。

NxのReadmeでも、「@<i>{このプロジェクトをお楽しみになられた方は、Project Numbat}@<fn>{numbat_hogo_1}@<i>{やAustralian Wildlife Conservancy}@<fn>{numbat_hogo_2}@<i>{などのNumbatの保護活動への寄付をご検討ください。}」との記述があります。

サポートしたいと思った方は寄付してみてはいかがでしょう。@<fn>{numbat_hogo_3}

//indepimage[numbat_02][実際のヌンバット][scale=0.5]{
//}

===[/column]

===[column] コラム：Introducing Nx - José Valim | Lambda Days 2021

2021年2月の@<b>{Lambda Days カンファレンス}でJosé Valim氏が語ったNxの紹介動画@<fn>{nx_jose_youtube}がYouTubeにあがっています。

===[/column]

//footnote[numbat_hogo_1][@<href>{https://www.numbat.org.au/}]
//footnote[numbat_hogo_2][@<href>{https://www.australianwildlife.org/}]
//footnote[numbat_hogo_3][ただ、日本から寄付するのは面倒かもしれません。以前、Project NumbatからPayPal経由で寄付しようとしたら、『この国からの寄付には対応してません』的なメッセージが出て寄付できませんでした。]
//footnote[nx_jose_youtube][@<href>{https://www.youtube.com/watch?v=fPKMmJpAGWc}]
