/*

    Refrence build to get a working version of lvgl running on a WioTerminal

*/
#include <lvgl.h>
#include <TFT_eSPI.h>

#define LVGL_TICK_PERIOD             5
#define TIME_STEP                   50

TFT_eSPI tft;
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
static lv_style_t screen_style;
static lv_style_t object_style;
static lv_indev_t *indev_keypad;
static lv_indev_t *indev_button;
static lv_disp_t *display;
static lv_group_t *select_group;

// the three button points to touch on the buttons
const lv_point_t button_area_points[] =  {
    {40,                       (LV_VER_RES_MAX - 40)},
    {(LV_HOR_RES_MAX / 2),     (LV_VER_RES_MAX - 40)},
    {(LV_HOR_RES_MAX - 40),    (LV_VER_RES_MAX - 40)},
};

// Display flushing
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint16_t c;

    tft.startWrite(); /* Start new TFT transaction */
    tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
    for (int y = area->y1; y <= area->y2; y++) {
        for (int x = area->x1; x <= area->x2; x++) {
            c = color_p->full;
            tft.writeColor(c, 1);
            color_p++;
        }
    }
    tft.endWrite(); /* terminate TFT transaction */
    lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        Serial.print("Clicked: ");
        Serial.println(lv_list_get_btn_text(obj));
    }
    else if(event == LV_EVENT_VALUE_CHANGED) {
        Serial.println("Toggled");
    }
    /*
    Serial.print(lv_obj_get_x(obj));
    Serial.print(" ");
    Serial.print(lv_obj_get_y(obj));
    Serial.print(" ");
    Serial.print(lv_obj_get_x(obj) + lv_obj_get_width(obj));
    Serial.print(" ");
    Serial.println(lv_obj_get_y(obj) + lv_obj_get_height(obj));
    */
}

// read the 3 buttons as a button encoder
bool button_reader(lv_indev_drv_t * drv, lv_indev_data_t*data){
    static int8_t last_button_id = 0;   /*Store the last pressed button*/
    int8_t button_id = -1;
    if (digitalRead(WIO_KEY_A) == LOW) {
        button_id = 2;
    }
    else if (digitalRead(WIO_KEY_B) == LOW) {
        button_id = 1;
    }
    else if (digitalRead(WIO_KEY_C) == LOW) {
        button_id = 0;
    }

    if (last_button_id != button_id) {               /*Is there a button press? (E.g. -1 indicated no button was pressed)*/
        last_button_id = button_id;           /*Save the ID of the pressed button*/
        if (button_id >=0 ) {
            Serial.print("button PRESS #");
            Serial.println(button_id, HEX);
            data->state = LV_INDEV_STATE_PR;  /*Set the pressed state*/
        }
        else {
            Serial.println("button RELEASE");
            data->state = LV_INDEV_STATE_REL; /*Set the released state*/
        }
        data->btn_id = last_button_id;            /*Save the last button*/
    }
    return false;                    /*No buffering now so no more data read*/
}

// read the 5 way switch using a keypad encoder
bool keypad_reader(lv_indev_drv_t* dev, lv_indev_data_t* data)
{
    static int32_t last_key = 0;
    int32_t key = 0;

    if (digitalRead(WIO_5S_UP) == LOW) {
        key = LV_KEY_UP;
    }
    else if (digitalRead(WIO_5S_DOWN) == LOW) {
        key = LV_KEY_DOWN;
    }
    else if (digitalRead(WIO_5S_LEFT) == LOW) {
        key = LV_KEY_NEXT;
    }
    else if (digitalRead(WIO_5S_RIGHT) == LOW) {
        key = LV_KEY_PREV;
    }
    else if (digitalRead(WIO_5S_PRESS) == LOW) {
        key = LV_KEY_ENTER;
    }
    if ( key != last_key) {
        last_key = key;
        if (key) {
            data->state = LV_INDEV_STATE_PR;
            Serial.print("key PRESS ");
            Serial.println(key, HEX);
        }
        else {
            data->state = LV_INDEV_STATE_REL;
            Serial.println("key RELEASE");
        }
        data->key = last_key;
    }
    return false;
}

void toolbar_buttons(void)
{
    // create the left button
    lv_obj_t * label;
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);
    lv_obj_add_style(btn1, LV_OBJ_PART_MAIN, &object_style);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Left");
    // add buton to group
    lv_group_add_obj(select_group, btn1);

    // create middle button
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(btn2, LV_OBJ_PART_MAIN, &object_style);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Center");
    // add buton to group
    lv_group_add_obj(select_group, btn2);

    // create right toggle button
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn3, event_handler);
    lv_obj_align(btn3, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
    lv_btn_set_checkable(btn3, true);
    lv_btn_toggle(btn3);
    lv_btn_set_fit2(btn3, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_add_style(btn3, LV_OBJ_PART_MAIN, &object_style);

    label = lv_label_create(btn3, NULL);
    lv_label_set_text(label, "Right");
    // add buton to group
    lv_group_add_obj(select_group, btn3);
}

void test_list_box(void)
{
    /*Create a list*/
    lv_obj_t * list1 = lv_list_create(lv_scr_act(), NULL);
    lv_obj_set_size(list1, 160, 200);
    lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    /*Add buttons to the list*/
    lv_obj_t * list_btn;

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "New");
    lv_obj_set_event_cb(list_btn, event_handler);
    // lv_obj_set_state(list_btn, LV_STATE_FOCUSED);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Open");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_BELL, "Notify");
    lv_obj_set_event_cb(list_btn, event_handler);

    list_btn = lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "Battery");
    lv_obj_set_event_cb(list_btn, event_handler);
    lv_group_add_obj(select_group, list1);
}

void setup() {
    // init the 5 way switch
    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);

    // init the 3 buttons
    pinMode(WIO_KEY_A, INPUT_PULLUP);
    pinMode(WIO_KEY_B, INPUT_PULLUP);
    pinMode(WIO_KEY_C, INPUT_PULLUP);

    Serial.begin(115200);

    tft.begin(); /* TFT init */
    tft.setRotation(3); /* Landscape orientation */
    lv_init();

    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    // Setup  the display driver
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    display = lv_disp_drv_register(&disp_drv);
    lv_style_init(&screen_style);
    lv_style_set_bg_color(&screen_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &screen_style);

    lv_style_init(&object_style);
    lv_style_set_border_color(&object_style, LV_STATE_FOCUSED, LV_COLOR_LIME);
    lv_style_set_border_width(&object_style, LV_STATE_FOCUSED, 4);

    // Setup the 5 way switch keypad encoder
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_reader;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    // Setup the 3 button encoder
    lv_indev_drv_t indev_buttons_driver;
    lv_indev_drv_init(&indev_buttons_driver);
    indev_buttons_driver.type = LV_INDEV_TYPE_BUTTON;
    indev_buttons_driver.read_cb = button_reader;
    indev_button = lv_indev_drv_register(&indev_buttons_driver);
    lv_indev_set_button_points(indev_button, button_area_points);

    // setup group for the 5 way switch
    select_group = lv_group_create();

    toolbar_buttons();

    // assign the 5 way switch to group
    lv_indev_set_group(indev_keypad, select_group);
}

void loop() {
    lv_tick_inc(LVGL_TICK_PERIOD);
    lv_task_handler();                         // let the GUI do its work
    delay(5);
}
