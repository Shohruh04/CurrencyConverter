#pragma once
#using <System.Windows.Forms.DataVisualization.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Windows::Forms::DataVisualization::Charting;

namespace cashconvert {

    public ref class MyForm : public Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            // Применяем тёмную тему ко всей форме и её элементам
            ApplyDarkThemeToControl(this);

            // Инициализация дополнительных компонентов
            InitComboBoxes();
            LoadFlags();
            InitExchangeRates();
            InitCharts();
            randomGenerator = gcnew Random();

            // Подписка на события
            textBox1_left->TextChanged += gcnew EventHandler(this, &MyForm::textBox1_left_TextChanged);
            textBox2_right->TextChanged += gcnew EventHandler(this, &MyForm::textBox2_right_TextChanged);
            comboBox1_left->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::comboBox1_left_SelectedIndexChanged);
            comboBox2_right->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::comboBox2_right_SelectedIndexChanged);
            button1->Click += gcnew EventHandler(this, &MyForm::button1_Click);
            button2->Click += gcnew EventHandler(this, &MyForm::button2_Click);
            button3->Click += gcnew EventHandler(this, &MyForm::button3_Click);
            button4->Click += gcnew EventHandler(this, &MyForm::button4_Click);
            button5->Click += gcnew EventHandler(this, &MyForm::button5_Click);

            // По умолчанию отображаем график за 1 день
            UpdateCharts(1);
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // Элементы управления
        PictureBox^ pictureBox1_left;
        PictureBox^ pictureBox2_right;
        TextBox^ textBox1_left;
        TextBox^ textBox2_right;
        ComboBox^ comboBox1_left;
        ComboBox^ comboBox2_right;
        Chart^ chartLeft;
        Chart^ chartRight;
        Panel^ panel1;
        Panel^ panel2;
        Button^ button1;
        Button^ button2;
        Button^ button3;
        Button^ button4;
        Button^ button5;
        PerformanceCounter^ performanceCounter1;
        PerformanceCounter^ performanceCounter2;
        Random^ randomGenerator;
        Dictionary<String^, double>^ currencyRates;
        Dictionary<String^, String^>^ flagPaths;
        bool isUpdating = false;

        // Используем IContainer для хранения компонентов
        IContainer^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Создаём элементы управления
            this->pictureBox1_left = gcnew PictureBox();
            this->pictureBox2_right = gcnew PictureBox();
            this->textBox1_left = gcnew TextBox();
            this->textBox2_right = gcnew TextBox();
            this->comboBox1_left = gcnew ComboBox();
            this->comboBox2_right = gcnew ComboBox();
            this->panel1 = gcnew Panel();
            this->panel2 = gcnew Panel();
            this->button1 = gcnew Button();
            this->button2 = gcnew Button();
            this->button3 = gcnew Button();
            this->button4 = gcnew Button();
            this->button5 = gcnew Button();

            // Инициализация PerformanceCounter с нужными свойствами
            this->performanceCounter1 = gcnew PerformanceCounter();
            this->performanceCounter1->CategoryName = "Processor";
            this->performanceCounter1->CounterName = "% Processor Time";
            this->performanceCounter1->InstanceName = "_Total";

            this->performanceCounter2 = gcnew PerformanceCounter();
            this->performanceCounter2->CategoryName = "Memory";
            this->performanceCounter2->CounterName = "Available MBytes";

            (cli::safe_cast<ISupportInitialize^>(this->pictureBox1_left))->BeginInit();
            (cli::safe_cast<ISupportInitialize^>(this->pictureBox2_right))->BeginInit();
            (cli::safe_cast<ISupportInitialize^>(this->performanceCounter1))->BeginInit();
            (cli::safe_cast<ISupportInitialize^>(this->performanceCounter2))->BeginInit();
            this->SuspendLayout();

            // Настройка pictureBox1_left
            this->pictureBox1_left->Location = Point(12, 12);
            this->pictureBox1_left->Name = "pictureBox1_left";
            this->pictureBox1_left->Size = Drawing::Size(87, 52);
            this->pictureBox1_left->SizeMode = PictureBoxSizeMode::Zoom;
            this->pictureBox1_left->TabIndex = 0;
            this->pictureBox1_left->TabStop = false;
            this->pictureBox1_left->Anchor = AnchorStyles::Top | AnchorStyles::Left;

            // Настройка pictureBox2_right
            this->pictureBox2_right->Location = Point(366, 12);
            this->pictureBox2_right->Name = "pictureBox2_right";
            this->pictureBox2_right->Size = Drawing::Size(100, 52);
            this->pictureBox2_right->SizeMode = PictureBoxSizeMode::Zoom;
            this->pictureBox2_right->TabIndex = 1;
            this->pictureBox2_right->TabStop = false;
            this->pictureBox2_right->Anchor = AnchorStyles::Top | AnchorStyles::Right;

            // Настройка textBox1_left
            this->textBox1_left->Location = Point(12, 70);
            this->textBox1_left->Name = "textBox1_left";
            this->textBox1_left->Size = Drawing::Size(100, 20);
            this->textBox1_left->TabIndex = 4;
            this->textBox1_left->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

            // Настройка textBox2_right
            this->textBox2_right->Location = Point(366, 70);
            this->textBox2_right->Name = "textBox2_right";
            this->textBox2_right->Size = Drawing::Size(100, 20);
            this->textBox2_right->TabIndex = 5;
            this->textBox2_right->Anchor = AnchorStyles::Top | AnchorStyles::Right;

            // Настройка comboBox1_left
            this->comboBox1_left->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboBox1_left->Location = Point(120, 70);
            this->comboBox1_left->Name = "comboBox1_left";
            this->comboBox1_left->Size = Drawing::Size(121, 21);
            this->comboBox1_left->TabIndex = 6;
            this->comboBox1_left->Anchor = AnchorStyles::Top | AnchorStyles::Left;

            // Настройка comboBox2_right
            this->comboBox2_right->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboBox2_right->Location = Point(239, 70);
            this->comboBox2_right->Name = "comboBox2_right";
            this->comboBox2_right->Size = Drawing::Size(121, 21);
            this->comboBox2_right->TabIndex = 7;
            this->comboBox2_right->Anchor = AnchorStyles::Top | AnchorStyles::Right;

            // Настройка panel1
            this->panel1->BackColor = Color::FromArgb(45, 45, 48);
            this->panel1->Location = Point(12, 160);
            this->panel1->Name = "panel1";
            this->panel1->Size = Drawing::Size(229, 157);
            this->panel1->TabIndex = 8;
            this->panel1->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left;

            // Настройка panel2
            this->panel2->BackColor = Color::FromArgb(45, 45, 48);
            this->panel2->Location = Point(247, 160);
            this->panel2->Name = "panel2";
            this->panel2->Size = Drawing::Size(229, 157);
            this->panel2->TabIndex = 9;
            this->panel2->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Right;

            // Настройка кнопок
            this->button1->Location = Point(42, 128);
            this->button1->Name = "button1";
            this->button1->Size = Drawing::Size(75, 26);
            this->button1->TabIndex = 10;
            this->button1->Text = "1 day";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Anchor = AnchorStyles::Top | AnchorStyles::Left;

            this->button2->Location = Point(123, 128);
            this->button2->Name = "button2";
            this->button2->Size = Drawing::Size(75, 26);
            this->button2->TabIndex = 11;
            this->button2->Text = "1 week";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Anchor = AnchorStyles::Top;

            this->button3->Location = Point(204, 128);
            this->button3->Name = "button3";
            this->button3->Size = Drawing::Size(75, 26);
            this->button3->TabIndex = 12;
            this->button3->Text = "1 month";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Anchor = AnchorStyles::Top;

            this->button4->Location = Point(285, 128);
            this->button4->Name = "button4";
            this->button4->Size = Drawing::Size(75, 26);
            this->button4->TabIndex = 13;
            this->button4->Text = "6 month";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Anchor = AnchorStyles::Top | AnchorStyles::Right;

            this->button5->Location = Point(366, 128);
            this->button5->Name = "button5";
            this->button5->Size = Drawing::Size(75, 26);
            this->button5->TabIndex = 14;
            this->button5->Text = "1 year";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Anchor = AnchorStyles::Top | AnchorStyles::Right;

            // Настройка формы
            this->AutoScaleDimensions = Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

            this->BackColor = Color::FromArgb(30, 30, 30);
            this->ClientSize = Drawing::Size(478, 329);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->comboBox2_right);
            this->Controls->Add(this->comboBox1_left);
            this->Controls->Add(this->textBox2_right);
            this->Controls->Add(this->textBox1_left);
            this->Controls->Add(this->pictureBox2_right);
            this->Controls->Add(this->pictureBox1_left);
            this->Name = "MyForm";
            this->Text = "Currency Converter";

            (cli::safe_cast<ISupportInitialize^>(this->pictureBox1_left))->EndInit();
            (cli::safe_cast<ISupportInitialize^>(this->pictureBox2_right))->EndInit();
            (cli::safe_cast<ISupportInitialize^>(this->performanceCounter1))->EndInit();
            (cli::safe_cast<ISupportInitialize^>(this->performanceCounter2))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        // Метод для рекурсивного применения тёмной темы ко всем контролам
        void ApplyDarkThemeToControl(Control^ ctrl)
        {
            ctrl->BackColor = Color::FromArgb(45, 45, 48);
            ctrl->ForeColor = Color::White;

            Button^ btn = dynamic_cast<Button^>(ctrl);
            if (btn != nullptr)
            {
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->BackColor = Color::FromArgb(45, 45, 48);
                btn->MouseEnter += gcnew EventHandler(this, &MyForm::Button_MouseEnter);
                btn->MouseLeave += gcnew EventHandler(this, &MyForm::Button_MouseLeave);
            }

            for each (Control ^ child in ctrl->Controls)
            {
                ApplyDarkThemeToControl(child);
            }
        }

        // Обработчик наведения для кнопок – меняем цвет на более тёмный
        System::Void Button_MouseEnter(Object^ sender, EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr)
            {
                btn->BackColor = Color::FromArgb(28, 28, 28);
            }
        }

        // Обработчик ухода курсора – возвращаем исходный цвет
        System::Void Button_MouseLeave(Object^ sender, EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr)
            {
                btn->BackColor = Color::FromArgb(45, 45, 48);
            }
        }

        // Инициализация ComboBox'ов с валютами
        void InitComboBoxes()
        {
            array<String^>^ currencies = gcnew array<String^> { L"USD", L"UZS", L"EUR", L"RUB", L"KZT", L"UAH", L"GBP" };
            comboBox1_left->Items->AddRange(currencies);
            comboBox2_right->Items->AddRange(currencies);
            comboBox1_left->SelectedIndex = 0;
            comboBox2_right->SelectedIndex = 1;
        }

        // Загрузка путей к изображениям флагов
        void LoadFlags()
        {
            flagPaths = gcnew Dictionary<String^, String^>();
            flagPaths->Add(L"USD", L"C:\\cash_convert\\flag\\usd.png");
            flagPaths->Add(L"UZS", L"C:\\cash_convert\\flag\\uzb.png");
            flagPaths->Add(L"EUR", L"C:\\cash_convert\\flag\\gr.png");
            flagPaths->Add(L"RUB", L"C:\\cash_convert\\flag\\rus.png");
            flagPaths->Add(L"KZT", L"C:\\cash_convert\\flag\\kz.png");
            flagPaths->Add(L"UAH", L"C:\\cash_convert\\flag\\uk.png");
            flagPaths->Add(L"GBP", L"C:\\cash_convert\\flag\\grb.png");
            flagPaths->Add(L"INR", L"C:\\cash_convert\\flag\\India.png");
        }

        // Инициализация курсов валют
        void InitExchangeRates()
        {
         currencyRates = gcnew Dictionary<String^, double>();
currencyRates->Add(L"USD", 1.0);        // US Dollar
currencyRates->Add(L"UZS", 12926.0);    // Uzbekistani Som
currencyRates->Add(L"EUR", 0.9268);     // Euro
currencyRates->Add(L"GBP", 0.7743);     // British Pound
currencyRates->Add(L"RUB", 84.8707);    // Russian Ruble
currencyRates->Add(L"KZT", 503.9640);   // Kazakhstani Tenge
currencyRates->Add(L"UAH", 36.0);       // Ukrainian Hryvnia
currencyRates->Add(L"INR", 85.64);      // Indian Rupee
        }

        // Инициализация графиков с настройкой осей, серий и белых подписей чисел
        void InitCharts()
        {
            chartLeft = gcnew Chart();
            chartRight = gcnew Chart();
            ChartArea^ areaLeft = gcnew ChartArea("MainArea");
            ChartArea^ areaRight = gcnew ChartArea("MainArea");

            // Форматирование осей: подписанные числа белого цвета
            areaLeft->AxisX->LabelStyle->Format = "dd/MM";
            areaLeft->AxisX->IntervalType = DateTimeIntervalType::Days;
            areaLeft->AxisX->LabelStyle->ForeColor = Color::White;
            areaLeft->AxisY->LabelStyle->ForeColor = Color::White;

            areaRight->AxisX->LabelStyle->Format = "dd/MM";
            areaRight->AxisX->IntervalType = DateTimeIntervalType::Days;
            areaRight->AxisX->LabelStyle->ForeColor = Color::White;
            areaRight->AxisY->LabelStyle->ForeColor = Color::White;

            chartLeft->ChartAreas->Add(areaLeft);
            chartRight->ChartAreas->Add(areaRight);

            Series^ seriesLeft = gcnew Series("Rate");
            seriesLeft->ChartType = SeriesChartType::Line;
            seriesLeft->XValueType = ChartValueType::DateTime;
            seriesLeft->Color = Color::Red; // красная линия
            chartLeft->Series->Add(seriesLeft);

            Series^ seriesRight = gcnew Series("Rate");
            seriesRight->ChartType = SeriesChartType::Line;
            seriesRight->XValueType = ChartValueType::DateTime;
            seriesRight->Color = Color::Red;
            chartRight->Series->Add(seriesRight);

            // Тёмный фон графиков
            chartLeft->BackColor = Color::FromArgb(45, 45, 48);
            chartRight->BackColor = Color::FromArgb(45, 45, 48);

            chartLeft->Dock = DockStyle::Fill;
            chartRight->Dock = DockStyle::Fill;
            panel1->Controls->Add(chartLeft);
            panel2->Controls->Add(chartRight);
        }

        // Обработчик изменения текста в textBox1_left
        System::Void textBox1_left_TextChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (isUpdating) return;
            try
            {
                isUpdating = true;
                double leftValue = 0.0;
                if (Double::TryParse(textBox1_left->Text, leftValue))
                {
                    String^ leftCurrency = comboBox1_left->SelectedItem->ToString();
                    String^ rightCurrency = comboBox2_right->SelectedItem->ToString();
                    double result = ConvertCurrency(leftValue, leftCurrency, rightCurrency);
                    textBox2_right->Text = result.ToString("F2");
                }
                else
                {
                    textBox2_right->Text = "";
                }
            }
            finally
            {
                isUpdating = false;
            }
        }

        // Обработчик изменения текста в textBox2_right
        System::Void textBox2_right_TextChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (isUpdating) return;
            try
            {
                isUpdating = true;
                double rightValue = 0.0;
                if (Double::TryParse(textBox2_right->Text, rightValue))
                {
                    String^ rightCurrency = comboBox2_right->SelectedItem->ToString();
                    String^ leftCurrency = comboBox1_left->SelectedItem->ToString();
                    double result = ConvertCurrency(rightValue, rightCurrency, leftCurrency);
                    textBox1_left->Text = result.ToString("F2");
                }
                else
                {
                    textBox1_left->Text = "";
                }
            }
            finally
            {
                isUpdating = false;
            }
        }

        // Обработчики изменения выбранного элемента в ComboBox'ах
        System::Void comboBox1_left_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            String^ leftCurrency = comboBox1_left->SelectedItem->ToString();
            if (flagPaths->ContainsKey(leftCurrency))
            {
                pictureBox1_left->Image = Image::FromFile(flagPaths[leftCurrency]);
            }
            UpdateLeftToRight();
            UpdateChartsForCurrency(true);
        }

        System::Void comboBox2_right_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            String^ rightCurrency = comboBox2_right->SelectedItem->ToString();
            if (flagPaths->ContainsKey(rightCurrency))
            {
                pictureBox2_right->Image = Image::FromFile(flagPaths[rightCurrency]);
            }
            UpdateLeftToRight();
            UpdateChartsForCurrency(false);
        }

        // Метод конвертации валют
        double ConvertCurrency(double amount, String^ from, String^ to)
        {
            if (!currencyRates->ContainsKey(from) || !currencyRates->ContainsKey(to))
                return 0.0;
            double inUSD = amount / currencyRates[from];
            double result = inUSD * currencyRates[to];
            return result;
        }

        // Метод обновления конвертации
        void UpdateLeftToRight()
        {
            if (textBox1_left->Text->Length > 0)
            {
                textBox1_left_TextChanged(nullptr, nullptr);
            }
        }

        // Метод обновления графиков за заданный период (в днях)
        void UpdateCharts(int periodDays)
        {
            DateTime endTime = DateTime::Now;
            DateTime startTime = endTime.AddDays(-periodDays);
            String^ leftCurrency = comboBox1_left->SelectedItem->ToString();
            String^ rightCurrency = comboBox2_right->SelectedItem->ToString();
            double baseLeft = currencyRates[leftCurrency];
            double baseRight = currencyRates[rightCurrency];
            int pointsCount = 10;
            chartLeft->Series["Rate"]->Points->Clear();
            for (int i = 0; i < pointsCount; i++)
            {
                double fraction = (double)i / (pointsCount - 1);
                DateTime timePoint = startTime.AddTicks((endTime - startTime).Ticks * i / (pointsCount - 1));
                double fluctuationLeft = (randomGenerator->NextDouble() - 0.5) * 0.1;
                double valueLeft = baseLeft * (1 + fluctuationLeft);
                chartLeft->Series["Rate"]->Points->AddXY(timePoint, valueLeft);
            }
            chartLeft->ChartAreas["MainArea"]->AxisX->Minimum = startTime.ToOADate();
            chartLeft->ChartAreas["MainArea"]->AxisX->Maximum = endTime.ToOADate();

            chartRight->Series["Rate"]->Points->Clear();
            for (int i = 0; i < pointsCount; i++)
            {
                double fraction = (double)i / (pointsCount - 1);
                DateTime timePoint = startTime.AddTicks((endTime - startTime).Ticks * i / (pointsCount - 1));
                double fluctuationRight = (randomGenerator->NextDouble() - 0.5) * 0.1;
                double valueRight = baseRight * (1 + fluctuationRight);
                chartRight->Series["Rate"]->Points->AddXY(timePoint, valueRight);
            }
            chartRight->ChartAreas["MainArea"]->AxisX->Minimum = startTime.ToOADate();
            chartRight->ChartAreas["MainArea"]->AxisX->Maximum = endTime.ToOADate();
        }

        // Метод обновления графиков для выбранной валюты (обновляем оба графика за последние 30 дней)
        void UpdateChartsForCurrency(bool isLeft)
        {
            UpdateCharts(30);
        }

        // Обработчики нажатия кнопок для смены периода графика
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
        {
            UpdateCharts(1);
        }
        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
        {
            UpdateCharts(7);
        }
        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
        {
            UpdateCharts(30);
        }
        System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
        {
            UpdateCharts(180);
        }
        System::Void button5_Click(System::Object^ sender, System::EventArgs^ e)
        {
            UpdateCharts(365);
        }
    };
}
