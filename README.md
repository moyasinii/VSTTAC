# preamp-plugin

名機マイクプリアンプ（Neve 1073 のプリアンプ部）を回路図から学び、VST プラグインとして再現する学習プロジェクト。

## ロードマップ

- [ ] Phase 1: Python で「マイクプリらしい音」の要素（トランス特性・飽和・倍音）を試す
- [ ] Phase 2: 回路図をブロックに分けて読み解く
- [ ] Phase 3: 回路定数にもとづくモデルに置き換える
- [ ] Phase 4: JUCE (C++) で VST3 プラグイン化

## フォルダ構成

- `python/` … Phase 1〜3 のプロトタイプ用スクリプト
- `plugin/` … JUCE (C++) の VST3 プラグイン本体
- `.github/workflows/build.yml` … GitHub Actions で Windows 用 VST3 を自動ビルド

## プラグインの入手（GitHub Actions）

1. `plugin/` を変更して push すると、自動でビルドが始まる（Actions タブから手動実行も可）
2. Actions タブ → 最新の実行 → 下部の Artifacts から `PreampPlugin-VST3-Windows` をダウンロード
3. zip を展開し、`Preamp Plugin.vst3` を `C:\Program Files\Common Files\VST3` に置く
4. DAW でプラグインを再スキャン

## 使い方（Phase 1）

```
pip install numpy scipy matplotlib soundfile
cd python
python first_test.py
```

`python/` に `input.wav` を置いてから実行すると、`output.wav` が書き出されます。
音声ファイルは `.gitignore` でリポジトリに含めないようにしています。

## 注意

個人の学習目的のプロジェクトです。公開・配布する場合、製品名に他社の商標は使用しません。
