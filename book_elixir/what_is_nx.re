= Nxってなんだろう

さて、Nxとはなんでしょうか？

本章では、Nxについて簡単に説明します。

== Nxとは

Nxとは、プログラミング言語Elixir用の@<b>{テンソルライブラリ}@<fn>{nx_descr}です。

「@<b>{N}umerical Eli@<b>{x}ir」から命名されています。

呼び方は「@<b>{エヌエックス}」が一般的です。

#@# ※ここに、マスコットキャラのウォンバットの画像を載せるか？。

//footnote[nx_descr][公式ページでは、「Multi-dimensional arrays (tensors) and numerical definitions for Elixir」と紹介されています。]

　

テンソルライブラリとは、文字通り"@<b>{テンソル}"を取り扱うライブラリです。
テンソルとは、「@<b>{ベクトルや行列を一般化したもの}」@<fn>{tensor}を指します。
数学では、ベクトルは1次元配列、行列は2次元配列を指します。そして、3次元配列以上の多次元配列が一般的にテンソルという扱いです。

ただし、本書では話を単純化するために、ベクトルや行列も含めたN次元配列をテンソルと呼びます。

//footnote[tensor][実際にはもっと詳しい定義があります。詳細はWikipediaなどを参照してください。]

多次元配列とは何かといえば、以下のようなものになります。

@<m>{\begin{bmatrix\} a & b \\\\ c & d \\\\ \end{bmatrix\}}

Nxは、Elixirの作者である@<b>{José Valim}氏の肝いりプロジェクトです。
Elixirを動かすために必要な@<b>{Erlang}@<fn>{erlang}にプルリクエストを投げてNxが性能を出せるようにした、という程の力の入れようです。
言語の作者本人が作成しているので、ライブラリのフォローなどの保証は十分にあると考えて良いでしょう。

//footnote[erlang][Erlang：アーランと呼びます。ElixirはErlang VM上で動くプログラム言語です。]


次の章では、Nxを利用して、実際にテンソルの計算をしてみましょう。

===[column] コラム：Nxのマスコット「ウォンバット」

Nxのプロジェクトのマスコットは「ウォンバット」と呼ばれる動物です。
絶滅の危機に瀕しているらしく、募金が集められたいます。

（→以前書いたブログの内容を少し直して載せる。）

===[/column]
