= 作るアプリについて

今回作るTODOリストアプリについての仕様を明確にしておきます。

== 仕様について

TODOリストの画面とTODO詳細画面の２画面からなるアプリです。

//image[screen_transition][画面遷移]{
//}

各画面の使用については、次の通りです。

 * TODOリスト画面
 ** TODOを一覧表示する
 ** それぞれについてname・descriptionを参照できる
 ** それぞれについてdone/undoneをできる
 ** フィルターできる
 * TODO詳細画面
 ** name・descriptionを参照できる
 ** done/undoneをできる

== API通信について

本来であればAPIを通してデータの取得や更新を行うのですが、今回はサーバーは用意しないので、API通信したように見せかけるだけで、実際にはAPIは叩かずにオンメモリでTODOリストを持つようにしています。
実装時は@<code>{todo-api}モジュールにある@<code>{TodoApiClient}@<fn>{api_client}を使用します。
@<code>{TodoApiClient}は、RxJava@<fn>{rx_java}の@<code>{Single}や@<code>{Completable}の型を返り値として、それらを@<code>{subscribe}した際にAPIを叩く振る舞いをする想定です。

//image[api][todo-apiモジュールのTodoApiClientを通して、データのやり取りをする]{
//}

//footnote[rx_java][https://github.com/ReactiveX/RxJava]
//footnote[api_client][https://github.com/kgmyshin/ride-on-jetpack/blob/master/modules/todo-api/src/main/java/com/kgmyshin/todo/api/TodoApiClient.kt]