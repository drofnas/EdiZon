#include "widget_value.hpp"

#include <math.h>

#define ACCELERATION_DELAY 50

WidgetValue::WidgetValue(LuaSaveParser *saveParser, s32 minValue, s32 maxValue, u32 stepSize) : Widget(saveParser), m_minValue(minValue), m_maxValue(maxValue), m_stepSize(stepSize) {
  m_widgetDataType = INT;

  if (stepSize == 0)
    m_stepSize = floor((maxValue - minValue) / 500.0F);
}

WidgetValue::~WidgetValue() {

}

void WidgetValue::draw(Gui *gui, u16 x, u16 y) {
  std::stringstream ss;
  ss << Widget::getIntegerValue();

  gui->drawTextAligned(font20, x + WIDGET_WIDTH - 140, y + (WIDGET_HEIGHT / 2.0F), currTheme.selectedColor, ss.str().c_str(), ALIGNED_RIGHT);
}

void WidgetValue::onInput(u32 kdown) {
  static u32 accelerationTimer = 0;

  if (kdown & KEY_LEFT) {
    accelerationTimer++;
    if (Widget::getIntegerValue() > m_minValue) {
      if(accelerationTimer > ACCELERATION_DELAY && Widget::getIntegerValue() > static_cast<s32>(m_minValue + m_stepSize))
        Widget::setIntegerValue(Widget::getIntegerValue() - m_stepSize);
      else
        Widget::setIntegerValue(Widget::getIntegerValue() - 1);
    }
    else Widget::setIntegerValue(m_maxValue);
  }

  if (kdown & KEY_RIGHT) {
    accelerationTimer++;
    if (Widget::getIntegerValue() < m_maxValue) {
      if(accelerationTimer > 50 && Widget::getIntegerValue() < static_cast<s32>(m_maxValue - m_stepSize))
        Widget::setIntegerValue(Widget::getIntegerValue() + m_stepSize);
      else
        Widget::setIntegerValue(Widget::getIntegerValue() + 1);
    }
    else Widget::setIntegerValue(m_minValue);
  }

  if ((kdown & (KEY_LEFT | KEY_RIGHT)) == 0 ||
      static_cast<s32>(Widget::getIntegerValue() - m_stepSize) <= m_minValue || static_cast<s32>(Widget::getIntegerValue() + m_stepSize) >= m_maxValue)
    accelerationTimer = 0;
}

void WidgetValue::onTouch(touchPosition &touch) {

}
