= Elixirのインストール

== Dockerを利用する場合

#@#Dockerを利用して、Elixir1.12をインストールする

おDockerを利用できるのであれば、Dockerを利用するのが手軽です。

Docker Hubには、Elixir公式のDockerのイメージ@<fn>{elixir_dockerhub}があります。

2021年7月10日時点では、@<b>{Elixir 1.12}系のDockerファイルの「From」には「@<b>{erlang:24}」が指定されています。
そのため、Nxを問題なく利用できます。@<fn>{elixir_dockerhub_1_12}

以下、Elixir 1.12のDockerコンテナを生成／起動するコマンドです。

//list[docker_elixir_run1][DockerでElixirを動かす]{
$ docker run -it --rm elixir:1.12 /bin/bash
//}

上記コマンド実行後は、コンテナ起動後にコンテナに入ります。
elixir／iexなどのコマンドが実行可能です。

//list[docker_elixir_run2][DockerコンテナでElixirの動作確認]{
root@ece9bfd7c98b:/# elixir --version
Erlang/OTP 24 [erts-12.0.3] [source] [64-bit]
   [smp:2:2] [ds:2:2:10] [async-threads:1] [jit]

Elixir 1.12.2 (compiled with Erlang/OTP 24)
root@ece9bfd7c98b:/#
root@ece9bfd7c98b:/# iex
Erlang/OTP 24 [erts-12.0.3] [source] [64-bit]
   [smp:2:2] [ds:2:2:10] [async-threads:1] [jit]

Interactive Elixir (1.12.2) - press Ctrl+C to exit
                            (type h() ENTER for help)
//}

また、コンテナ内に入らずにホスト側でElixirコマンドを実行したければ、elixirやiexを指定してdockerコマンドを実行します。

//list[docker_elixir_run3_1][ホスト側でElixirを動かす1：elixirコマンドの実行]{
$ docker run -it --rm elixir:1.12 elixir --version
//}

//list[docker_elixir_run3_2][ホスト側でElixirを動かす2：iexコマンドの実行]{
$ docker run -it --rm elixir:1.12 iex
//}

//footnote[elixir_dockerhub][@<href>{https://hub.docker.com/_/elixir}]

//footnote[elixir_dockerhub_1_12][1.12系より前のバージョンでは、erlang:23以前のバージョンで定義されているので、そのままではNxは利用できません。]


== asdfを利用する場合

asdfを利用して、Elixir1.12をインストールする


===[column] Catalinaへasdfをインストールする際の留意点

山崎先生のQiitaの記事に関する内容を紹介

===[/column]

== 補足：asdf自体をインストールする場合

asdfをインストールする場合はここを読んでね。