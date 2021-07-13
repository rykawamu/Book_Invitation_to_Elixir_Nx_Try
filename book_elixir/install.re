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

#@# asdfを利用して、Elixir1.12をインストールする

@<b>{asdf}とは、CLIベースのバージョン管理ツール@<fn>{asdf_homepage}です。
特定言語に対して複数のランタイムバージョンを管理できます。

//footnote[asdf_homepage][@<href>{https://asdf-vm.com/#/}]

asdfがインストールされていない場合は、以下のURLを参照してasdfを実行できるようにしてください。
なお、本書ではasdfのインストールに関しては説明は割愛します。

　

@<href>{https://asdf-vm.com/#/core-manage-asdf}

　

asdfがインストール後、プログラム言語をインストールします。
インストールするものは、@<b>{Erlang}と@<b>{Elixir}です。

以下の順序でインストールをしていきます。

 * Erlang 24.x系をインストールする
 ** Before asdf installに従って必要なライブラリをインストールする
 ** Erlangインストール用のプラグインをインストールする
 ** Erlangの利用バージョンを指定する
 * Elixir 1.12系（otp24）をインストールする
 ** Erlangインストール用のプラグインをインストールする
 ** Erlangの利用バージョンを指定する

asdf経由でErlangをインストールする場合には、以下URLの内容にしたがってセットアップしてください。
本書では、簡略化して説明します。

　

@<href>{https://github.com/asdf-vm/asdf-erlang}

　

Erlangをインストールする前に、必要なライブラリをインストールします。
インストールするライブラリはOSによって異なるので、詳細は以下のURLを参照してください。

　

@<href>{https://github.com/asdf-vm/asdf-erlang#before-asdf-install}

　

以下、macOSのHomebrewでインストールする前提でのライブラリのインストール手順です。

//list[asdf_install_before_erlang][macOSで必要なライブラリ]{
$ brew install autoconf
$ brew install openssl
$ brew install wxmac
//}

必要なライブラリをインストール後、asdfのErlangプラグインをインストールします。

//list[asdf_install_plugin_erlang][asdf-erlangプラグインのインストール]{
$ asdf plugin-add erlang https://github.com/asdf-vm/asdf-erlang.git
//}

Erlangのプラグインインストール後、Erlang24系のインストールを実施します。
本書では、「24.0.2」をインストールしています。

なお、Erlangのインストールには10-15分程度の時間がかかります。気長にお待ちください。

//list[asdf_install_erlang][erlang 24.0.2のインストール]{
$ asdf install erlang 24.0.2
//}

インストール完了後、先ほどインストールした「erlang 24.0.2」を利用可能にします。

//list[asdf_global_erlang][erlang 24.0.2を利用可能にする]{
$ asdf global erlang 24.0.2
//}

つづいて、Elixirをインストールしていきます。

asdf経由でElixirをインストールする場合には、以下URLの内容にしたがってセットアップしてください。
本書では、簡略化して説明します。

　

@<href>{https://github.com/asdf-vm/asdf-elixir}

　

//list[asdf_install_plugin_elixir][asdf-elixirプラグインのインストール]{
$ asdf plugin-add elixir https://github.com/asdf-vm/asdf-elixir.git
//}

Elixirのプラグインインストール後、Elixir 1.12系OTP24のインストールを実施します。
本書では、「1.12.1-otp-24」をインストールしています。
なお、Elixirのインストールはすぐに完了します。

//list[asdf_install_elixir][elixir 1.12.1-otp-24のインストール]{
$ asdf install elixir 1.12.1-otp-24
//}

インストール完了後、先ほどインストールした「elixir 1.12.1-otp-24」を利用可能にします。

//list[asdf_global_elixir][elixir 1.12.1-otp-24を利用可能にする]{
$ asdf global elixir 1.12.1-otp-24
//}

//list[asdf_confirm_elixir][elixirが起動するか確認する]{
$elixir --version
Erlang/OTP 24 [erts-12.0.2] [source] [64-bit]
    [smp:4:4] [ds:4:4:10] [async-threads:1] [jit]

Elixir 1.12.1 (compiled with Erlang/OTP 24)

$iex
Erlang/OTP 24 [erts-12.0.2] [source] [64-bit]
    [smp:4:4] [ds:4:4:10] [async-threads:1] [jit]

Interactive Elixir (1.12.1) - press Ctrl+C to exit
                            (type h() ENTER for help)
iex(1)>
//}



===[column] コラム：Catalinaへasdfをインストールする際の留意点

macOSの「@<b>{Catalina}」へasdfをインストールする場合は、以下2点の留意点があります。

 * kerlにパッチを当てる
 * @<b>{DED_LDFLAGS}を付与してErlangをインストールする

詳細については、山崎進（@zacky1972）氏の書かれたQiitaの記事@<fn>{asdf_catalina}をご参照ください。

===[/column]

//footnote[asdf_catalina][@<href>{https://qiita.com/zacky1972/items/b8963ac3eeca7e1edf36}]
