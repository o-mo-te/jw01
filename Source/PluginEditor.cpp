#include "PluginEditor.h"

// 親クラスのコンストラクタを呼び出し、プロセッサへの参照を保持
TestAudioProcessorEditor::TestAudioProcessorEditor(JW01AudioProcessor& p): AudioProcessorEditor(&p), processor(p) {
    // ゲインスライダーのスタイルを設定（横方向のリニアスライダー）
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    // テキストボックスのスタイルを設定（右側に配置、サイズは 80x20）
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    // スライダーをエディタに追加し、可視化
    addAndMakeVisible(gainSlider);
    // ゲインスライダーを AudioProcessorValueTreeState に接続し、パラメータと連動
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                                                                                            processor.parameters, "gain", gainSlider
                                                                                            );
    // エディタのウィンドウサイズを 750x500 に設定
    setSize(750, 500);
}

// デストラクタ（特にリソースの解放処理は不要）
TestAudioProcessorEditor::~TestAudioProcessorEditor() {}

// エディタの描画処理
void TestAudioProcessorEditor::paint(juce::Graphics& g) {
    // 背景を黒に塗りつぶす
    g.fillAll(juce::Colours::black);
    // テキストの色を白に設定
    g.setColour(juce::Colours::white);
    // フォントサイズを 15.0f に設定
    g.setFont(15.0f);
    // プラグイン名 "Gain Plugin" を、上部中央に描画
    g.drawFittedText("Gain Plugin", getLocalBounds(), juce::Justification::centredTop, 1);
}

// コンポーネントのリサイズ時にスライダーの位置を調整
void TestAudioProcessorEditor::resized() {
    // スライダーの位置を設定(左端から 20px, 上から 40px, 横幅はウィンドウ幅 - 40px, 高さは 20px)
    gainSlider.setBounds(20, 40, getWidth() - 40, 20);
}
