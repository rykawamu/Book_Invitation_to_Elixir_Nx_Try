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

=== Nx.type/1

引数で渡されたテンソルの型を返す。

数値を直接渡した場合でも処理は可能。

//list[nx_type_01_1][テンソルを判定する：2次元テンソル]{
iex> t_type_1a = Nx.tensor([[1,2],[3,4]])
#Nx.Tensor<
  s64[2][2]
  [
    [1, 2],
    [3, 4]
  ]
>

iex> Nx.type(t_type_1a)
{:s, 64}
//}

//list[nx_type_01_2][テンソルを判定する：型指定したテンソルの確認]{
iex> t_type_1b = Nx.tensor([[1,2],[3,4]], type: {:f, 32})
#Nx.Tensor<
  f32[2][2]
  [
    [1.0, 2.0],
    [3.0, 4.0]
  ]
>
//}

//list[nx_type_02_1][テンソルを判定する：スカラーの場合]{
iex> Nx.type(Nx.tensor(10))
{:s, 64}
iex> Nx.type(Nx.tensor(10.1))
{:f, 32}
//}

//list[nx_type_02_2][テンソルを判定する：数値の場合はそのまま引数に渡せる]{
iex> Nx.type(10)
{:s, 64}

iex> Nx.type(10.1)
{:f, 32}
//}

//list[nx_type_03][テンソルを判定する：テンソルになっていない場合はエラー]{
iex> Nx.type([1,2,3])
** (ArgumentError) expected a %Nx.Tensor{} or a number, got: [1, 2, 3]
    (nx 0.1.0-dev) lib/nx.ex:1170: Nx.to_tensor/1
    (nx 0.1.0-dev) lib/nx.ex:2217: Nx.type/1
//}

=== Nx.compatible?/2

引数で渡した2つのテンソルが、同じ形状／タイプか、そして互換性のある名前を持っているかチェックします。

なお、テンソル内のデータはチェックされません。

//list[nx_compatible_01][テンソルが同じ形状／タイプか判定する：テンソルを渡す1]{
iex> t_compati_1 = Nx.tensor([[1,2],[3,4]])
#Nx.Tensor<
  s64[2][2]
  [
    [1, 2],
    [3, 4]
  ]
>

iex> t_compati_2 = Nx.tensor([[5,6],[7,8]])
#Nx.Tensor<
  s64[2][2]
  [
    [5, 6],
    [7, 8]
  ]
>

iex> Nx.compatible?(t_compati_1, t_compati_2)
true
//}

テンソルのタイプが同じでも、形状が異なればfalseを返す。

//list[nx_compatible_02][テンソルが同じ形状／タイプか判定する：テンソルを渡す2]{
iex> t_compati_1 = Nx.tensor([[1,2],[3,4]])
#Nx.Tensor<
  s64[2][2]
  [
    [1, 2],
    [3, 4]
  ]
>

iex> t_compati_3 = Nx.tensor([[1,2],[3,4],[5,6]])
#Nx.Tensor<
  s64[3][2]
  [
    [1, 2],
    [3, 4],
    [5, 6]
  ]
>

iex> Nx.compatible?(t_compati_1, t_compati_3)
false
//}

テンソルの形状が同じでも、タイプが異なればfalseを返す。

//list[nx_compatible_03][テンソルが同じ形状／タイプか判定する：テンソルを渡す3]{
iex> t_compati_1 = Nx.tensor([[1,2],[3,4]])
#Nx.Tensor<
  s64[2][2]
  [
    [1, 2],
    [3, 4]
  ]
>

iex> t_compati_4 = Nx.tensor([[1.0, 2.0],[3,4]])
#Nx.Tensor<
  f32[2][2]
  [
    [1.0, 2.0],
    [3.0, 4.0]
  ]
>

iex> Nx.compatible?(t_compati_1, t_compati_4)
false
//}

以下の例では、前者は形状／タイプが同じになるが、後者の場合はタイプが変わる。

//list[nx_compatible_04][テンソルが同じ形状／タイプか判定する：数値を渡す]{
iex> Nx.compatible?(1, 3)
true

iex> Nx.compatible?(1, 1.0)
false
//}

両方とも名前なしの場合、もしくは片方飲み名前がある場合は、同じと判定。

//list[nx_compatible_05_1][テンソルが同じ形状／タイプか判定する：名前の際による判定結果1]{
iex> Nx.compatible?(Nx.iota({3, 2}), Nx.iota({3, 2}))
true

iex> Nx.compatible?(
...>   Nx.iota({3, 2}),
...>   Nx.iota({3, 2},names: [:rows, :columns])
...> )
true
//}

片方の名前がnilの場合は同一と判定される。ただし、両方に名前が振られていおり、かつ異なる名前の場合は同じではないと判定される。

//list[nx_compatible_05_2][テンソルが同じ形状／タイプか判定する：名前の際による判定結果2]{
iex> Nx.compatible?(
...>   Nx.iota({3, 2},names: [nil, :columns]),
...>   Nx.iota({3, 2},names: [:rows, nil])
...> )
true

iex> Nx.compatible?(
...>   Nx.iota({3, 2},names: [:rows, :columns]),
...>   Nx.iota({3, 2},names: [:gyo, :columns])
...> )
false
//}

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


=== Nx.sum/2

テンソルの和を返します。

「@<b>{:axes}」オプションが与えられている場合は、与えられた次元の上で集約します。

「@<b>{axes: [0]}」は最高次数の次元に集約することを意味します。
次元以上に集約することを意味します。
軸が負の場合はその軸を後ろから数えます。
例えば、「@<b>{axes: [-1]}」と入力すると、常にすべての行を集計します。

//list[nx_sum_1][テンソルの和：スカラー]{
iex> Nx.sum(42)
#Nx.Tensor<
  s64
  42
>
//}

//list[nx_sum_2][テンソルの和：ベクトル]{
iex> Nx.sum(Nx.tensor([2,4,6,8,8,10,12,16]))
#Nx.Tensor<
  s64
  66
>
//}

//list[nx_sum_3][テンソルの和：行列]{
iex> Nx.sum(Nx.tensor([[2,4],[6,8],[8,10],[12,16]]))
#Nx.Tensor<
  s64
  66
>
//}

//list[nx_sum_99][テンソルの和：axesオプションによる和の違い]{
iex> tsum1 = Nx.tensor([[[2,4],[6,8]],[[8,10],[12,16]]])
#Nx.Tensor<
  s64[2][2][2]
  [
    [
      [2, 4],
      [6, 8]
    ],
    [
      [8, 10],
      [12, 16]
    ]
  ]
>

iex> Nx.sum(tsum1)
#Nx.Tensor<
  s64
  66
>

iex> Nx.sum(tsum1, axes: [0])
#Nx.Tensor<
  s64[2][2]
  [
    [10, 14],
    [18, 24]
  ]
>

iex> Nx.sum(tsum1, axes: [1])
#Nx.Tensor<
  s64[2][2]
  [
    [8, 12],
    [20, 26]
  ]
>

iex> Nx.sum(tsum1, axes: [2])
#Nx.Tensor<
  s64[2][2]
  [
    [6, 14],
    [18, 28]
  ]
>

iex> Nx.sum(tsum1, axes: [-1])
#Nx.Tensor<
  s64[2][2]
  [
    [6, 14],
    [18, 28]
  ]
>
//}


===[column] コラム：Nx.expについて

ソフトマックス関数で利用した「Nx.exp」については、実はNxの関数ではありません。

def unary_math_funsの定義の1つです。

exp: {"exponential", quote(do: :math.exp(var!(x)))},

https://github.com/elixir-nx/nx/blob/main/nx/lib/nx/shared.ex

===[/column]

== Nxの今後

TODO: KerasやAxonについて何かかければ。