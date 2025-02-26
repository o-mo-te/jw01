#include "JW01AudioProcessorEditor.h"

// 親クラスのコンストラクタを呼び出し、プロセッサへの参照を保持
JW01AudioProcessorEditor::JW01AudioProcessorEditor(JW01AudioProcessor& p): AudioProcessorEditor(&p), processor(p) {
    // オーバードライブスライダーのスタイルを設定しエディタに追加&AudioProcessorValueTreeStateに接続しパラメータと連動
    overdriveSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    overdriveSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(overdriveSlider);
    NotificationName overdrive = NotificationName::Overdrive;
    std::string overdriveString = std::string(toString(overdrive));
    overdriveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, overdriveString, overdriveSlider);
    
    // エディタのウィンドウサイズを設定
    setSize(750, 500);
}

// デストラクタ（特にリソースの解放処理は不要）
JW01AudioProcessorEditor::~JW01AudioProcessorEditor() {}

// エディタの描画処理
void JW01AudioProcessorEditor::paint(juce::Graphics& g) {
    // 背景を黒に塗りつぶす
    g.fillAll(juce::Colours::black);
    // テキストの色を白に設定
    g.setColour(juce::Colours::white);
    // フォントサイズを 15.0f に設定
    g.setFont(15.0f);
    // プラグイン名を上部中央に描画
    g.drawFittedText("JW01 Plugin", getLocalBounds(), juce::Justification::centredTop, 1);
}

// コンポーネントのリサイズ時にスライダーの位置を調整
void JW01AudioProcessorEditor::resized() {
    // スライダーの位置を設定(左端から 20px, 上から 40px, 横幅はウィンドウ幅 - 40px, 高さは 20px)
    overdriveSlider.setBounds(20, 40, getWidth() - 40, 20);
}
