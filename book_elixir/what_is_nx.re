= Nxってなんだろう

さて、Nxとはなんでしょうか？

本章では、Nxについて簡単に説明します。

== Nxとは

Nxとは、プログラミング言語Elixir用の@<b>{テンソルライブラリ}@<fn>{nx_descr}です。

「@<b>{N}umerical Eli@<b>{x}ir」から命名されています。

呼び方は「@<b>{エヌエックス}」が一般的です。

ロゴには、一見するとリスにも見えるマスコットキャラ「@<b>{ヌンバット}」が描かれています。

//indepimage[numbat_01][Nxのロゴ（GitHub公式ページより拝借）][scale=0.5]{
//}


//footnote[nx_descr][公式ページでは、「Multi-dimensional arrays (tensors) and numerical definitions for Elixir」と紹介されています。]

　

テンソルライブラリとは、文字通り"@<b>{テンソル}"を取り扱うライブラリです。
テンソルとは、「@<b>{ベクトルや行列を一般化したもの}」@<fn>{tensor}を指します。
数学では、ベクトルは1次元配列、行列は2次元配列を指します。そして、3次元配列以上の多次元配列が一般的にテンソルという扱いです。

ただし、本書では話を単純化するために、ベクトルや行列も含めたN次元配列をテンソルと呼びます。

//footnote[tensor][実際はもっと詳しい定義があります。詳細はWikipediaなどを参照してください。]

多次元配列とは何かといえば、以下のようなものになります。

//blankline

@<m>{\begin{bmatrix\} a & b & c \\\\ d & e & f \\\\ \end{bmatrix\}}

//blankline

Nxは、Elixirの作者である@<b>{José Valim}氏の肝いりプロジェクトです。
Elixirを動かすために必要な@<b>{Erlang}@<fn>{erlang}にプルリクエストを投げ、Nxが性能を出せるようにしたという程の力の入れようです。@<fn>{nx_version}
言語の作者本人が作成しているので、ライブラリのフォローなどの保証は十分にあると考えて良いでしょう。

次の章では、Nxを利用して、実際にテンソルの計算をしてみましょう。

//footnote[erlang][「アーラン」と呼びます。ElixirはErlang VM上で動くプログラム言語です。]

//footnote[nx_version][ただし、これによってNxを動かすためのバージョン指定は厳しくなりました。]

===[column] コラム：Nxのマスコット「ヌンバット」

Nxのプロジェクトのマスコットは「Numbat（ヌンバット）」と呼ばれる動物です。
一見するとリスのようですが、和名だと「フクロアリクイ」と呼ばれています。

//indepimage[numbat_02][実際のヌンバット][scale=0.5]{
//}

ヌンバットは、オーストラリア南部原産の有袋類です。
絶滅の危機（推定では1000頭以下）に瀕しているらしく、募金が集められています。

NxのReadmeでも、「@<i>{このプロジェクトをお楽しみになられた方は、Project Numbat}@<fn>{numbat_hogo_1}@<i>{やAustralian Wildlife Conservancy}@<fn>{numbat_hogo_2}@<i>{などのNumbatの保護活動への寄付をご検討ください。}」との記述があります。

もし、サポートしたいと思われた方は寄付してみてはいかがでしょうか。@<fn>{numbat_hogo_3}

===[/column]

//footnote[numbat_hogo_1][@<href>{https://www.numbat.org.au/}]
//footnote[numbat_hogo_2][@<href>{https://www.australianwildlife.org/}]
//footnote[numbat_hogo_3][ただ、日本から寄付するのは面倒かもしれません。以前、Project NumbatからPayPal経由で寄付しようとしたら、『この国からの寄付には対応してません』的なメッセージが出て寄付できませんでした。]
