= はじめてのNx

== Nxの扉を開いてみよう

Nxは、テンソル計算用ライブラリと説明しました。

細かな説明は後述するとして、まずはNxライブラリを動かしてみましょう。

本書では次の環境下で動作確認を行なっております。

 * Erlang 24.0.2
 * Elixir 1.12.1-otp-24
 * OS: macOS 11.4（Big Sur）

本書の内容を実施する場合には、こちらにバージョンを合わせるか、これ以上のバージョン@<fn>{otp24}にしてください。
OSについては、macOS以外ではLinux環境で実施するのが望ましいです。@<fn>{os_select}

//footnote[otp24][NxはOTP24以降が必須のため、Erlangのバージョンは必然的にErlang24以降となります。]
//footnote[os_select][WindowsインストーラがOTP24未対応のため、Windows上では動作できません。ただし、WSL2上でなら動作実績があるようです。]

インストール方法については、付録で解説していますのでそちらを参照ください。

Elixir 1.12系が動く環境下で、ファイル「@<b>{practice.exs}」を作成します。
エディタを利用して、入力してください。

//list[nx_practice_exs][practice.exsを作成する]{

Mix.install([{:nx, "~> 0.1.0-dev",
   github: "elixir-nx/nx", branch: "main", sparse: "nx"}])

a = [[1, 2], [3, 4]]

#Example 1.1:
IO.puts("Example 1.1: create a tensor")

a
|> Nx.tensor()
|> IO.inspect()

#Example 1.2:
IO.puts("Example 1.2:tensor shape")

a
|> Nx.tensor()
|> Nx.shape()
|> IO.inspect()

#Example2
IO.puts("Example 2:softmax function")

divide = fn e -> Nx.divide(e, Nx.sum(e)) end

a
|> Nx.tensor()
|> Nx.exp()
|> divide.()
|> IO.inspect()

//}

簡単にソースの内容を解説します。

 * 1行目の@<b>{Mix.install}では、GitHub上からNxライブラリを読み込み、ローカルにインストールしています。
 * 2次元配列を模したリストを、@<b>{a}に束縛します。以降は、この二次元配列を利用します。
 * 各Exampleでは、以下を実施しています。
 ** Example 1.1: 2次元配列の"テンソル"を作成する
 ** Example 1.2: 作成した2次元配列のテンソルの"形状"（各次元の長さ）を確認する
 ** Example 2: "ソフトマックス関数"を実行する

　

ファイルを作成したら、以下のコマンドを実行します。
実行には少し時間（体感10-30秒程度）がかかります。

//list[nx_practice_exs2][practice.exsを実行する]{
$elixir practice.exs
//}

//list[nx_practice_exs3][practice.exsの実行結果を確認する]{
Example 1.1: create a tensor
#Nx.Tensor<
  s64[2][2]
  [
    [1, 2],
    [3, 4]
  ]
>

Example 1.2:tensor shape
{2, 2}

Example 2:softmax function
#Nx.Tensor<
  f32[2][2]
  [
    [0.032058604061603546, 0.08714432269334793],
    [0.23688282072544098, 0.6439142227172852]
  ]
>
//}

実行結果をみてみましょう。

 * Example 1.1: 「2行2列」の"テンソル"が作成された
 * Example 1.2: 「2行2列」のテンソルの"形状"が判明した。
 * Example 2: 全ての要素の合計値が「1」@<fn>{softmax_sum}になった。

//footnote[softmax_sum][0.03205+0.08714+0.23688+0.64391 -> 0.99998 ->ほぼ 1]


さて、これでNxの扉は開かれました。

　

次の章では、Nxで利用できるいくつかの関数の紹介をします。