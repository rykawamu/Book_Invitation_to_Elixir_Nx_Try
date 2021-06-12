= プロローグ

== Nxの扉を開いてみよう

Nxとは、Elixirで作成されたテンソルライブラリです。

と、細かな説明は後述するとして、Nxライブラリを使ってみた例を紹介しましょう。

なお、本書では以下の環境下で動作確認を行なっております。
本書の内容を実施する場合には、こちらにバージョンを合わせるか、これに近いバージョンにしてください。

 * Erlang 24.x
 * Elixir 1.12.x

インストール方法については、付録で解説していますのでそちらを参照ください。

Elixir 1.12系が動く環境下で、「practice.exs」を作成します。
エディッタを利用して、入力してください。

//list[nx_practice_exs][practice.exsを作成する]{

Mix.install([{:nx, "~> 0.1.0-dev", github: "elixir-nx/nx", branch: "main", sparse: "nx"}])

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

さて、これでNxの扉は開かれました。
次の章では、Nxについての説明と、Nxで利用できるいくつかの関数の紹介をします。