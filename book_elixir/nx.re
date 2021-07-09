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

#@# Creates a one-dimensional tensor from a `binary` with the given `type`.（1071行目）

バイナリ@<fn>{binary}と型を引数にして、1次元のテンソルを作成します。

バイナリに合わない型を指定すると、例外が発生します。

//list[nx_from_binary_01][バイナリでテンソルを作る1]{
iex> Nx.from_binary(<<100>>, {:s, 8})
#Nx.Tensor<
  s8[1]
  [100]
>

iex> Nx.from_binary(<<12.4::float-64-native>>, {:f, 64})
#Nx.Tensor<
  f64[1]
  [12.4]
>
//}

//list[nx_from_binary_02][バイナリでテンソルを作る2]{
iex> Nx.from_binary(<<104,111,103>>, {:s, 8})
#Nx.Tensor<
  s8[3]
  [104, 111, 103, 101, 0]
>
//}

文字列もバイナリであるので、文字列とバイナリを連結して渡すことも可能。

//list[nx_from_binary_03][バイナリでテンソルを作る3]{
iex> Nx.from_binary("hoge" <> <<0>>, {:s, 8})
#Nx.Tensor<
  s8[5]
  [104, 111, 103, 101, 0]
>
//}

合わない型を指定した場合は、例外が発生します。

//list[nx_from_binary_04][バイナリでテンソルを作る4：エラー発生]{
iex> Nx.from_binary(<<104,111,103>>, {:f, 32})
** (ArgumentError) binary does not match the given size
    (nx 0.1.0-dev) lib/nx.ex:1109: Nx.from_binary/3
//}


//footnote[binary][Elixirのバイナリとは、バイトのシーケンスです。1バイトでは、0から255の数値を表現します。Elixirでは、文字列もバイナリです。]

=== Nx.iota/2

#@# Creates a tensor with the given shape which increments along the provided axis. You may optionally provide dimension  names.（865行目）

指定された@<b>{軸}（axis）に沿って増分する、指定された形状のテンソルを作成します。

オプションで次元名を指定することもできます。

軸が指定されていない場合、indexは各要素でカウントアップされます。

テンソルまたは数値が指定された場合、形状と名前はテンソルから取得されます。

//list[nx_iota_01][増分するテンソルを作る1：タプルの利用]{
iex> Nx.iota({})
#Nx.Tensor<
  s64
  0
>

iex> Nx.iota({1})
#Nx.Tensor<
  s64[1]
  [0]
>

iex> Nx.iota({1,2})
#Nx.Tensor<
  s64[1][2]
  [
    [0, 1]
  ]
>

iex> Nx.iota({1,2,3})
#Nx.Tensor<
  s64[1][2][3]
  [
    [
      [0, 1, 2],
      [3, 4, 5]
    ]
  ]
>

iex> Nx.iota({3,3,3})
#Nx.Tensor<
  s64[3][3][3]
  [
    [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8]
    ],
    [
      [9, 10, 11],
      [12, 13, 14],
      [15, 16, 17]
    ],
    [
      [18, 19, 20],
      [21, 22, 23],
      [24, 25, 26]
    ]
  ]
>
//}

既存のテンソルを利用して、新しいテンソルを作成。形状と名前は引き継がれるが、タイプは引き継がれなかった。

//list[nx_iota_02][増分するテンソルを作る2：テンソルの利用]{
iex> t_iota_1 = Nx.tensor([2,4,6,8.0], names: [:even])
#Nx.Tensor<
  f32[even: 4]
  [2.0, 4.0, 6.0, 8.0]
>

iex> Nx.iota(t_iota_1)
#Nx.Tensor<
  s64[even: 4]
  [0, 1, 2, 3]
>
//}

軸を指定することで、作成されるテンソルのindeの値に変化がみえる。

//list[nx_iota_03][増分するテンソルを作る2：軸の指定]{
iex> Nx.iota({3, 3, 3})
#Nx.Tensor<
  s64[3][3][3]
  [
    [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8]
    ],
    [
      [9, 10, 11],
      [12, 13, 14],
      [15, 16, 17]
    ],
    [
      [18, 19, 20],
      [21, 22, 23],
      [24, 25, 26]
    ]
  ]
>

iex> Nx.iota({3, 3, 3}, axis: 0)
#Nx.Tensor<
  s64[3][3][3]
  [
    [
      [0, 0, 0],
      [0, 0, 0],
      [0, 0, 0]
    ],
    [
      [1, 1, 1],
      [1, 1, 1],
      [1, 1, 1]
    ],
    [
      [2, 2, 2],
      [2, 2, 2],
      [2, 2, 2]
    ]
  ]
>

iex> Nx.iota({3, 3, 3}, axis: 1)
#Nx.Tensor<
  s64[3][3][3]
  [
    [
      [0, 0, 0],
      [1, 1, 1],
      [2, 2, 2]
    ],
    [
      [0, 0, 0],
      [1, 1, 1],
      [2, 2, 2]
    ],
    [
      [0, 0, 0],
      [1, 1, 1],
      [2, 2, 2]
    ]
  ]
>

iex> Nx.iota({3, 3, 3}, axis: 2)
#Nx.Tensor<
  s64[3][3][3]
  [
    [
      [0, 1, 2],
      [0, 1, 2],
      [0, 1, 2]
    ],
    [
      [0, 1, 2],
      [0, 1, 2],
      [0, 1, 2]
    ],
    [
      [0, 1, 2],
      [0, 1, 2],
      [0, 1, 2]
    ]
  ]
>
//}

===  Nx.eye/2

#@#Creates the identity matrix of size `n`.（993行目）

サイズ「n」を指定して、@<b>{単位行列}@<fn>{identity_matrix}を作成します。

引数には、サイズ「n」以外にも、型やテンソルを渡せませす。ただし、渡せる型は、行列（2次元まで）となっています。

//footnote[identity_matrix][単位行列（たんいぎょうれつ、identity matrix）とは、正方行列の対角成分が1で、それ以外が零である行列を指す。]

//list[nx_eye_01][単位行列を作る1：数値の指定]{
iex> Nx.eye(1)
#Nx.Tensor<
  s64[1][1]
  [
    [1]
  ]
>

iex> Nx.eye(2)
#Nx.Tensor<
  s64[2][2]
  [
    [1, 0],
    [0, 1]
  ]
>

iex> Nx.eye(3)
#Nx.Tensor<
  s64[3][3]
  [
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
  ]
>

iex> Nx.eye(4)
#Nx.Tensor<
  s64[4][4]
  [
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]
  ]
>
//}

//list[nx_eye_02][単位行列を作る2：型の指定]{
iex> Nx.eye(3, type: {:s, 64})
#Nx.Tensor<
  s64[3][3]
  [
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
  ]
>

iex> Nx.eye(3, type: {:f, 64})
#Nx.Tensor<
  f64[3][3]
  [
    [1.0, 0.0, 0.0],
    [0.0, 1.0, 0.0],
    [0.0, 0.0, 1.0]
  ]
>

iex> Nx.eye(3, type: {:f, 32})
#Nx.Tensor<
  f32[3][3]
  [
    [1.0, 0.0, 0.0],
    [0.0, 1.0, 0.0],
    [0.0, 0.0, 1.0]
  ]
>
//}

//list[nx_eye_03][単位行列を作る3：テンソルの指定]{
iex> Nx.eye(Nx.iota({1,1}))
#Nx.Tensor<
  s64[1][1]
  [
    [1]
  ]
>

iex> Nx.eye(Nx.iota({2,2}))
#Nx.Tensor<
  s64[2][2]
  [
    [1, 0],
    [0, 1]
  ]
>

iex> Nx.eye(Nx.iota({3,3}))
#Nx.Tensor<
  s64[3][3]
  [
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
  ]
>
//}


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

=== Nx.shape/1

引数で渡されたテンソルの形状を、タプルで返します。
タプル形式で渡された場合には、そのタプルをそのまま返します。

//list[nx_shape_01][テンソルの形状確認1]{
iex> Nx.shape(1)
{}

iex> Nx.shape(Nx.tensor(1))
{}

iex> Nx.shape(Nx.tensor([1]))
{1}

iex> Nx.shape(Nx.tensor([1,2,3]))
{3}

iex> Nx.shape(Nx.tensor([[1,2,3],[4,5,6]]))
{2, 3}
//}

3次元のテンソルを渡してみる。

//list[nx_shape_02][テンソルの形状確認2]{
iex> Nx.tensor([[[1,2],[3,4],[5,6],[7,8]]])
#Nx.Tensor<
  s64[1][4][2]
  [
    [
      [1, 2],
      [3, 4],
      [5, 6],
      [7, 8]
    ]
  ]
>

iex> Nx.shape(Nx.tensor([[[1,2],[3,4],[5,6],[7,8]]]))
{1, 4, 2}
//}

タプル形式を引数に渡してみる。

//list[nx_shape_03][テンソルの形状確認3]{
iex> Nx.shape({})
{}

iex> Nx.shape({2})
{2}

iex> Nx.shape({4,2})
{4, 2}

iex> Nx.shape({1,4,2})
{1, 4, 2}
//}

テンソル形式にできないタプルの場合はエラーとなる。

//list[nx_shape_04][テンソルの形状確認4]{
iex(254)> Nx.shape({0})
** (ArgumentError) invalid dimension in axis 0 in shape. 
       Each dimension must be a positive integer, got 0 in shape {0}
    (nx 0.1.0-dev) lib/nx/shape.ex:35: Nx.Shape.validate!/3
//}

=== Nx.size/1

テンソルの@<b>{ランク}を返します。

形状としてタプルが与えられている場合、与えられたタプルのランクを計算します。

//list[nx_size_01][テンソルのランク確認1：テンソルを渡す]{
iex> Nx.rank(Nx.tensor(1))
0

iex> Nx.rank(Nx.tensor([1,2,3]))
1

iex> Nx.rank(Nx.tensor([[1,2,3],[4,5,6]]))
2

iex> Nx.rank(Nx.tensor([[1,2,3],[4,5,6],[7,8,9]]))
2

iex> Nx.rank(Nx.tensor([[[1,2,3],[4,5,6]],[[7,8,9],[10,11,12]]]))
3
//}

//list[nx_size_02][テンソルのランク確認2：タプルを渡す]{
ex> Nx.shape({})
{}

iex> Nx.shape({2})
{2}

iex> Nx.shape({4,2})
{4, 2}

iex> Nx.shape({1,4,2})
{1, 4, 2}
//}

//list[nx_size_03][テンソルのランク確認3：例外発生]{
iex(254)> Nx.shape({0})
** (ArgumentError) invalid dimension in axis 0 in shape.
 Each dimension must be a positive integer, got 0 in shape {0}
    (nx 0.1.0-dev) lib/nx/shape.ex:35: Nx.Shape.validate!/3
//}

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


=== Nx.power/2

2つのテンソルの要素ごとの累乗を返します。

数値が与えられた場合、それはテンソルに変換されます。

次元が一致せず、ブロードキャストが可能な場合は常にテンソルをブロードキャストします。次元が一致せず、ブロードキャストが可能な場合、テンソルをブロードキャストします。

両方のテンソルが整数で、指数が負の場合は、負であればレイズします。一方、コンパイラによっては未定義の動作を引き起こす可能性があります。

//list[nx_power_01][テンソルの累乗1：スカラーの累乗]{
iex> Nx.power(2, 4)
#Nx.Tensor<
  s64
  16
>

iex> Nx.power(3, 4)
#Nx.Tensor<
  s64
  81
>
//}

//list[nx_power_02][テンソルの累乗2：テンソルの累乗]{
iex> Nx.power(Nx.tensor([[1,2,3],[4,5,6]]), 4)
#Nx.Tensor<
  s64[2][3]
  [
    [1, 16, 81],
    [256, 625, 1296]
  ]
>
//}

//list[nx_power_03][テンソルの累乗3：ブロードキャスト演算]{
iex> Nx.power(Nx.tensor([[3], [5]]), Nx.tensor([[4, 5]]))
#Nx.Tensor<
  s64[2][2]
  [
    [81, 243],
    [625, 3125]
  ]
>
//}

//list[nx_power_04][テンソルの累乗4：指数が負の場合]{
iex> Nx.power(Nx.tensor([[1,2,3],[4,5,6]]), -1)
** (ArithmeticError) bad argument in arithmetic expression
    (elixir 1.12.1) lib/integer.ex:106: Integer.pow(1, -1)
    (nx 0.1.0-dev) lib/nx/binary_backend.ex:635:
      Nx.BinaryBackend."-element_wise_bin_op/4-lbc$^16/2-8-"/7
    (nx 0.1.0-dev) lib/nx/binary_backend.ex:634:
      Nx.BinaryBackend.element_wise_bin_op/4
//}

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