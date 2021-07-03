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

=== Nx.add/2

引数へ2つのテンソルを渡して、要素ごとに加算します。

2つのテンソルの次元・形状が異なっていても、ブロードキャスト@<fn>{broadcasting}演算が可能であれば計算されます。

//footnote[broadcasting][ブロードキャスト（broadcasting）とは、テンソルの次元・形状が異なる場合でも、条件に合致するならば自動で次元・形状を合わせて計算処理する仕組みです。]


//list[nx_add_01_1][テンソルの加算：スカラー]{
iex> Nx.add(1,2)
#Nx.Tensor<
  s64
  3
>
//}

//list[nx_add_02][テンソルの加算：ベクトル]{
iex> Nx.add(Nx.tensor([1,2,3]), Nx.tensor([4,5,6]))
#Nx.Tensor<
  s64[3]
  [5, 7, 9]
>
//}

//list[nx_add_03][テンソルの加算：行列]{
iex> t3 = Nx.tensor([[1,2,3],[4,5,6]])
#Nx.Tensor<
  s64[2][3]
  [
    [1, 2, 3],
    [4, 5, 6]
  ]
>

iex> t4 = Nx.tensor([[7,8,9],[10,11,12]])
#Nx.Tensor<
  s64[2][3]
  [
    [7, 8, 9],
    [10, 11, 12]
  ]
>

iex> Nx.add(t3, t4)
#Nx.Tensor<
  s64[2][3]
  [
    [8, 10, 12],
    [14, 16, 18]
  ]
>
//}

//list[nx_add_04_1][テンソルの加算：ブロードキャスト演算]{
iex> Nx.add(Nx.tensor([4,5,6]),3)
#Nx.Tensor<
  s64[3]
  [7, 8, 9]
>

iex> Nx.add(Nx.tensor([[1,2],[3,4]]),Nx.tensor([5,6]))
#Nx.Tensor<
  s64[2][2]
  [
    [6, 8],
    [8, 10]
  ]
>
//}

//list[nx_add_04_2][テンソルの加算：ブロードキャスト演算に失敗]{
iex> l3 = [[[1, 2], [3, 4], [5, 6]], [[-1, -2], [-3, -4], [-5, -6]]]
[[[1, 2], [3, 4], [5, 6]], [[-1, -2], [-3, -4], [-5, -6]]]

iex> tl3 = Nx.tensor(l3)
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

iex> Nx.add(tl3, Nx.tensor(1))
#Nx.Tensor<
  s64[2][3][2]
  [
    [
      [2, 3],
      [4, 5],
      [6, 7]
    ],
    [
      [0, -1],
      [-2, -3],
      [-4, -5]
    ]
  ]
>

iex> Nx.add(tl3, Nx.tensor([1,2]))
#Nx.Tensor<
  s64[2][3][2]
  [
    [
      [2, 4],
      [4, 6],
      [6, 8]
    ],
    [
      [0, 0],
      [-2, -2],
      [-4, -4]
    ]
  ]
>

iex> Nx.add(tl3, Nx.tensor([1,2,3]))
** (ArgumentError) cannot broadcast tensor of dimensions {2, 3, 2} to {3}
    (nx 0.1.0-dev) lib/nx/shape.ex:310: Nx.Shape.binary_broadcast/4
    (nx 0.1.0-dev) lib/nx.ex:2575: Nx.element_wise_bin_op/4
//}


=== Nx.subtract/2

引数へ2つのテンソルを渡して、要素ごとに減算します。

2つのテンソルの次元次元・形状が異なっていても、ブロードキャスト演算が可能であれば計算されます。

//list[nx_subtract_01_1][テンソルの減算：スカラー]{
iex> Nx.subtract(1,2)
#Nx.Tensor<
  s64
  -1
>
//}

//list[nx_subtract_02][テンソルの減算：ベクトル]{
iex> Nx.subtract(Nx.tensor([1,2,3]), Nx.tensor([5,7,9]))
#Nx.Tensor<
  s64[3]
  [-4, -5, -6]
>
//}

//list[nx_subtract_03][テンソルの減算：ブロードキャスト演算]{
iex> Nx.subtract(Nx.tensor([[1,2,3],[4,5,6]]), 5)
#Nx.Tensor<
  s64[2][3]
  [
    [-4, -3, -2],
    [-1, 0, 1]
  ]
>

iex> Nx.subtract(5, Nx.tensor([[1,2,3],[4,5,6]]))
#Nx.Tensor<
  s64[2][3]
  [
    [4, 3, 2],
    [1, 0, -1]
  ]
>
//}

=== Nx.multiply/2

引数へ2つのテンソルを渡して、要素ごとに乗算します。

2つのテンソルの次元次元・形状が異なっていても、ブロードキャスト演算が可能であれば計算されます。

//list[nx_multiply_01_1][テンソルの乗算：スカラー]{
iex> Nx.multiply(2,3)
#Nx.Tensor<
  s64
  6
>
//}

//list[nx_multiply_02][テンソルの乗算：ベクトル]{
iex> Nx.multiply(Nx.tensor([1,2,3]), Nx.tensor([5,7,9]))
#Nx.Tensor<
  s64[3]
  [5, 14, 27]
>
//}

//list[nx_multiply_03][テンソルの乗算：ブロードキャスト演算]{
iex> Nx.multiply(Nx.tensor([[1,2,3],[4,5,6]]), 5)
#Nx.Tensor<
  s64[2][3]
  [
    [5, 10, 15],
    [20, 25, 30]
  ]
>

iex> Nx.multiply(5.0, Nx.tensor([[1,2,3],[4,5,6]]))
#Nx.Tensor<
  f32[2][3]
  [
    [5.0, 10.0, 15.0],
    [20.0, 25.0, 30.0]
  ]
>
//}


=== power

階乗：2810

=== Nx.remainder/2

引数へ2つのテンソルを渡して、要素ごとに剰余を算出します。

2つのテンソルの次元次元・形状が異なっていても、ブロードキャスト演算が可能であれば計算されます。

//list[nx_remainder_01_1][テンソルの剰余：スカラー]{
iex> Nx.remainder(10,4)
#Nx.Tensor<
  s64
  2
>

iex> Nx.remainder(4,10)
#Nx.Tensor<
  s64
  4
>
//}

//list[nx_remainder_02][テンソルの剰余：ベクトル]{
iex> Nx.remainder(Nx.tensor([1,2,3]), Nx.tensor([5,7,9]))
#Nx.Tensor<
  s64[3]
  [1, 2, 3]
>

iex> Nx.remainder(Nx.tensor([5,7,9]), Nx.tensor([1,2,3]))
#Nx.Tensor<
  s64[3]
  [0, 1, 0]
>
//}

//list[nx_remainder_03][テンソルの剰余：ブロードキャスト演算]{
iex> Nx.remainder(20, Nx.tensor([3,5,15]) )
#Nx.Tensor<
  s64[3]
  [2, 0, 5]
>

iex> Nx.remainder(Nx.tensor([3,5,15]), 20)
#Nx.Tensor<
  s64[3]
  [3, 5, 15]
>
//}

=== divide

除算：2908

=== quotient

商：2988

=== Nx.max/2

引数へ2つのテンソルを渡して、要素ごとに比較して大きい値を算出します。

2つのテンソルの次元次元・形状が異なっていても、ブロードキャスト演算が可能であれば計算されます。

//list[nx_max_01_1][大きい値の算出：スカラー]{
iex> Nx.max(10,4)
#Nx.Tensor<
  s64
  10
>

iex> Nx.max(10.0, 10.001)
#Nx.Tensor<
  f32
  10.00100040435791
>
//}

//list[nx_max_02][大きい値の算出：ベクトル]{
iex> Nx.max(Nx.tensor([7,3,5,9]), Nx.tensor([2,4,6,8]))
#Nx.Tensor<
  s64[4]
  [7, 4, 6, 9]
>
//}

//list[nx_max_03][大きい値の算出：ブロードキャスト演算]{
iex> Nx.max(Nx.tensor([1,2,3]), 3)
#Nx.Tensor<
  s64[3]
  [3, 3, 3]
>

iex> Nx.max(Nx.tensor([2,4,6]), 3)
#Nx.Tensor<
  s64[3]
  [3, 4, 6]
>

iex> Nx.max(Nx.tensor([[2,4,8],[0,2,4]]), Nx.tensor([1,5,6]))
#Nx.Tensor<
  s64[2][3]
  [
    [2, 5, 8],
    [1, 5, 6]
  ]
>
//}

=== Nx.min/2

引数へ2つのテンソルを渡して、要素ごとに比較して小さい値を算出します。

2つのテンソルの次元次元・形状が異なっていても、ブロードキャスト演算が可能であれば計算されます。

//list[nx_min_01_1][小さい値の算出：スカラー]{
iex> Nx.min(10,4)
#Nx.Tensor<
  s64
  4
>

iex> Nx.min(10.0, 10.001)
#Nx.Tensor<
  f32
  10.0
>
//}

//list[nx_min_02][小さい値の算出：ベクトル]{
iex> Nx.min(Nx.tensor([7,3,5,9]), Nx.tensor([2,4,6,8]))
#Nx.Tensor<
  s64[4]
  [2, 3, 5, 8]
>
//}

//list[nx_min_03][小さい値の算出：ブロードキャスト演算]{
iex> Nx.min(Nx.tensor([1,2,3]), 3)
#Nx.Tensor<
  s64[3]
  [1, 2, 3]
>

iex> Nx.min(Nx.tensor([2,4,6]), 3)
#Nx.Tensor<
  s64[3]
  [2, 3, 3]
>

iex> Nx.min(Nx.tensor([[2,4,8],[0,2,4]]), Nx.tensor([1,5,6]))
#Nx.Tensor<
  s64[2][3]
  [
    [1, 4, 6],
    [0, 2, 4]
  ]
>
//}


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