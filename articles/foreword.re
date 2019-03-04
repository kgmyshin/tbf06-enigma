= まえがき

== 本書でのJetpackの扱い

Google I/O 2018でAndroid Jetpackが発表されました。
Android Jetpackとは、もともとあったAndroid Architecture Componentsやそのほかのライブラリをまとめたソフトウェア群で、
Androidアプリ開発をより簡単に行うためのものです。

本書では、Jetpackに乗りこなすためには何をすべきかを、サンプルとして定番のTODOリストアプリをつくることで説明していきたいと思います。

と、その前にまずJetpackを使うとはどういうことでしょうか。
一言でJetpackといってもその守備範囲はとても広いです。
ViewModelやLiveDataなどのAndroid Architecture Componentsに所属していたもの以外にも、
TestやMultiDexも含まれ、そしてAutoやTVもその一覧の中にあります。
これらすべてを本書の対象としてしまうと、辞典のようなものを作らなければならず、とても書き切ることができません。
そのため、@<b>{本書でのJetpackを使うとは、Android Architecture Componentsを使うことと同等とします}。

== 本書の目的

Android Architecture ComponentsやAndroid Jetpackについて、たとえば@<code>{LiveData}について深く説明したもの、
@<code>{ViewModel}について深く説明したものなどは、今までにも多くありました。
しかし、それらを実際にどう組み合わせて使うかについて触れたものは、あまり出回ってないようです。
本書の目的はまさにそこで、@<code>{LiveData}、@<code>{ViewModel}などをどう組み合わせて使っていくかの一例を知ってもらうことにあります。
そのため@<code>{LiveData}、@<code>{ViewModel}などについて、簡単な説明はしますが、数ページにわたっての詳細な説明はしていません。
それよりも、TODOリストアプリというサンプルアプリを作る際に、それらをどう組み合わせて使ったかに焦点を当てて説明するからです。
サンプルコードは下記にあります。必要な時にご参照ください。

#@# * @<href>{https://github.com/kgmyshin/ride-on-jetpack}
 * https://github.com/kgmyshin/ride-on-jetpack

== 対象読者

本書の対象読者は、Androidアプリ開発者全般です。
下記のような状況の方はドンピシャの内容となっていると思います。

 * @<code>{LiveData}、@<code>{ViewModel}などの内容をうっすら知っている
 * ただし、使ったことはないけど、どう使ったらいいか悩んでいる

もしくは、@<code>{LiveData}、@<code>{ViewModel}などの使い方の一例を見たい方も対象読者圏内のほぼ真ん中に当たると思います。