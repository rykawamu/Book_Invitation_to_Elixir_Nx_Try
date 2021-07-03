= Nxの関数を紹介

本章では、Nxで利用できる関数を紹介します。

== defnについて

== 使い方

=== mixプロジェクトを作成する場合

従来通り、mixプロジェクトを作成して利用する場合には、ファイル@<b>{mix.exs}中の@<b>{def deps do}の定義内で、以下の設定を追記する。

//list[nx_setting_mix][mix.exsでNxを設定する]{
def deps do
  [
    {:nx, "~> 0.1.0-dev", github: "elixir-nx/nx", branch: "main", sparse: "nx"}
  ]
end
//}

=== exsで利用する場合

== どんな関数があるのか

主に、テンソルを作成する関数と、テンソルに対して計算処理を行う関数があります。

なお、本書ではすべての関数は紹介しません。というよりも、しきれません。
代表的なものをご紹介しますので、興味のある方はより深く調査してみてください。

== テンソルを作成する関数

テンソルを関数として、以下の7つが用意されています。

 * tensor/2
 * from_binary/2
 * iota/2
 * eye/2
 * random_uniform/2
 * random_normal/2
 * broadcast/3

このうち、本書では「tensor/2」「from_binary/2」「iota/2」「eye/2」の4つを紹介します。

=== Nx.tensor/2

#@# Builds a tensor.（310行目）

引数で渡された値を、テンソルの型にして出力します。

引数には、以下の値を渡せます。

 * テンソルが@<b>{スカラー}（0次元テンソル）であることを意味する数値
 * テンソルが@<b>{ベクトル}（1次元テンソル）であることを意味するスカラーの集合したリスト
 * n次元のテンソルを意味する、n個のリスト。たとえば@<b>{行列}（2次元テンソル）は、ベクトルの集合したリスト。

それぞれの作成例を以下に示します。

//list[nx_tensor_01_1][スカラー（0次元）のテンソルを作成：整数]{
iex> Nx.tensor(0)
#Nx.Tensor<
  s64
  0
>
//}

//list[nx_tensor_01_2][スカラー（0次元）のテンソルを作成：実数]{
iex> Nx.tensor(1.0)
#Nx.Tensor<
  f32
  1.0
>
//}

//list[nx_tensor_02_1][ベクトル（1次元）のテンソルを作る：整数]{
iex> Nx.tensor([1, 2, 3])
#Nx.Tensor<
  s64[3]
  [1, 2, 3]
>
//}

//list[nx_tensor_02_2][ベクトル（1次元）のテンソルを作る：整数]{
iex> Nx.tensor([1.2, 2.3, 3.4, 4.5])
#Nx.Tensor<
  f32[4]
  [1.2000000476837158, 2.299999952316284, 3.4000000953674316, 4.5]
>
//}

//list[nx_tensor_03_1][n次元のテンソルを作る：2行3列の行列]{
iex> Nx.tensor([[1, 2, 3], [4, 5, 6]])
#Nx.Tensor<
  s64[2][3]
  [
    [1, 2, 3],
    [4, 5, 6]
  ]
>
//}

//list[nx_tensor_03_2][N次元のテンソルを作る：3行2列の行列]{
iex> Nx.tensor([[1, 2], [3, 4], [5, 6]])
#Nx.Tensor<
  s64[3][2]
  [
    [1, 2],
    [3, 4],
    [5, 6]
  ]
>
//}

//list[nx_tensor_03_3][N次元のテンソルを作る：3次元テンソル]{
iex> t3 = [
...>       [
...>         [1, 2], [3, 4], [5, 6]
...>       ],
...>       [
...>         [-1, -2], [-3, -4], [-5, -6]
...>       ]
...>     ]
iex> Nx.tensor(t3)
#Nx.Tensor<
  s64[2][3][2]
  [
    [
      [1, 2],
      [3, 4],
      [5, 6]
    ],
    [
      [-1, -2],
      [-3, -4],
      [-5, -6]
    ]
  ]
>
//}


=== from_binary/2

Creates a one-dimensional tensor from a `binary` with the given `type`.（1071行目）

=== iota/2

Creates a tensor with the given shape which increments along the provided axis. You may optionally provide dimension  names.（865行目）

===  eye/2

Creates the identity matrix of size `n`.（993行目）

== テンソルに対して計算処理を行う関数

=== Nx.type

2187

=== compatible?

2211

=== shape

2261

=== size

2320

=== add

加算：2561

=== subtract

引き算：2680

=== multiply

掛け算：2745

=== power

階乗：2810

=== Remainder

余：2879

=== divide

除算：2908

=== quotient

商：2988

=== max

3123

=== min

3188

=== sum

4633


===[column] コラム：Nx.expについて

ソフトマックス関数で利用した「Nx.exp」については、実はNxの関数ではありません。

def unary_math_funsの定義の1つです。

exp: {"exponential", quote(do: :math.exp(var!(x)))},

https://github.com/elixir-nx/nx/blob/main/nx/lib/nx/shared.ex

===[/column]

== Nxの今後

TODO: KerasやAxonについて何かかければ。