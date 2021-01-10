# robosys2020 ROS課題

### 概要
カメラが人間を検出すると指定したGmailに人間の顔の画像を送信します。

### 動作環境
|||
|:--:|:--:|
|OS|Ubuntu18.04LTS|
|ROS Distribution|ROS Melodic Morenia|

### インストール手順
#### 環境構築
以下を参考にしてROSの環境構築とワークスペースを作成する。
[ROSのインストール](http://wiki.ros.org/melodic/Installation)
[ワークスペースの作成](http://wiki.ros.org/ja/catkin/Tutorials/create_a_workspace)
[cv_cameraのインストール](http://wiki.ros.org/cv_camera)
#### クローン
レポジトリをクローン

```
$git clone https://github.com/Takagon/HumanDetectionSecurityCamera.git
```
#### ビルド
roscoreを起動
```
$roscore
```
クローンしてきたパッケージをビルド
```
$cd ~/catkin_ws
$catkin_make
$source ~/.bashrc
```
### 実行
カメラをパソコンに接続しcv_camera_nodeを起動する。
```
$rosrun cv_camera cv_camera_node
```
人検出ノードを起動する。
```
$rosrun HumanDetectionSecurityCamera imgsub
```
メール送信ノードを起動する。
```
$rosrun HumanDetectionSecurityCamera mailsend.py
```
