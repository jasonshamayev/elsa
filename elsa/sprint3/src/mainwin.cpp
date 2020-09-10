#include "mainwin.h"
#include "entrydialog.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>

Mainwin::Mainwin() : store{new Store}, filename("untitled.elsa") {


	set_default_size(600, 400);
	set_title("ELSA");

    // Put a vertical box container as the Window contents
    Gtk::Box* vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // /////// ////////////////////////////////////////////////////////////////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar* menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
     //vbox->add(*menubar);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem* menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    // V I E W
    Gtk::MenuItem* menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    // I N S E R T
    Gtk::MenuItem* menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu* insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);

    // H E L P
    Gtk::MenuItem* menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu* helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

   //           E A S T E R
   // Append Easter Egg to the Help menu
    Gtk::MenuItem* menuitem_easter = Gtk::manage(new Gtk::MenuItem("_Easter Egg", true));
    menuitem_easter->signal_activate().connect([this] {this->on_easter_egg_click(); });
    helpmenu->append(*menuitem_easter);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem* menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click(); });
    filemenu->append(*menuitem_quit);
 
  //         N E W
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] {this->on_new_store_click();});
    filemenu->append(*menuitem_new);


    //         O P E N
    Gtk::MenuItem* menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect([this] {this->on_open_click(); });
    filemenu->append(*menuitem_open);

    //        S A V E
    Gtk::MenuItem* menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect([this] {this->on_save_click(); });
    filemenu->append(*menuitem_save);

    //        S A V E  A S
    Gtk::MenuItem* menuitem_save_as = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_save_as->signal_activate().connect([this] {this->on_save_as_click(); });
    filemenu->append(*menuitem_save_as);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem* menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click(); });
    helpmenu->append(*menuitem_about);
//  VIEW
    // C U S T O M E R
    Gtk::MenuItem* menuitem_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_customer->signal_activate().connect([this] {this->on_view_customer_click(); });
    viewmenu->append(*menuitem_customer);

    // P E R I P H E R A L
    Gtk::MenuItem* menuitem_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_peripheral->signal_activate().connect([this] {this->on_view_peripheral_click(); });
    viewmenu->append(*menuitem_peripheral);

    // D E S K T O P
    Gtk::MenuItem* menuitem_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_desktop->signal_activate().connect([this] {this->on_view_desktop_click(); });
    viewmenu->append(*menuitem_desktop);

    // O R D E R
    Gtk::MenuItem* menuitem_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_order->signal_activate().connect([this] {this->on_view_order_click(); });
    viewmenu->append(*menuitem_order);

// INSERT
    // C U S T O M E R
    Gtk::MenuItem* menuitem_customer2 = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_customer2->signal_activate().connect([this] {this->on_insert_customer_click(); });
    insertmenu->append(*menuitem_customer2);

    // P E R I P H E R A L
    Gtk::MenuItem* menuitem_peripheral2 = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_peripheral2->signal_activate().connect([this] {this->on_insert_peripheral_click(); });
    insertmenu->append(*menuitem_peripheral2);

    // D E S K T O P
    Gtk::MenuItem* menuitem_desktop2 = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_desktop2->signal_activate().connect([this] {this->on_insert_desktop_click(); });
    insertmenu->append(*menuitem_desktop2);

    // O R D E R
    Gtk::MenuItem* menuitem_order2 = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_order2->signal_activate().connect([this] {this->on_insert_order_click(); });
    insertmenu->append(*menuitem_order2);

    // D A T A   D I S P L A Y
    data = Gtk::manage(new Gtk::Label{ "", Gtk::ALIGN_START, Gtk::ALIGN_START });
    data->set_hexpand();
    // A Gtk::Label is intrinsically transparent - it's background color cannot be set
    // Therefore, we add it to a Gtk::EventBox with background color overridden to white
    Gtk::EventBox* eb = Gtk::manage(new Gtk::EventBox);
    eb->set_hexpand();
    eb->override_background_color(Gdk::RGBA("white"));
    eb->add(*data);
    // PACK_EXPAND_WIDGET tells VBox this widget should be as big as possible
    vbox->pack_start(*eb, Gtk::PACK_EXPAND_WIDGET, 0);

    // S T A T U S   B A R   D I S P L A Y ////////////////////////////////////
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label);
    msg->set_hexpand();
    // PACK_SHRINK tells VBox this widget should be as small as possible
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start with a new store
    on_new_store_click();

}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

// COMBINED observer / callback

void Mainwin::on_quit_click(){
	close();
}
void Mainwin::on_view_peripheral_click()
{ 
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Peripherals</b></big><tt>\n\n";
    for (int i = 0; i < store->num_options(); ++i)
       oss << i << ") " << store->option(i) << "\n";
    oss << "</tt>";
    set_data(oss.str());
    set_msg("");

}

void Mainwin::on_view_desktop_click()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Products</b></big><tt>\n\n";
    for (int i = 0; i < store->num_desktops(); ++i)
        oss << i << ") " << store->desktop(i) << "\n";
    oss << "</tt>";
    set_data(oss.str());
    set_msg("");
}

void Mainwin::on_view_order_click()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Orders</b></big><tt>\n\n";
    for (int i = 0; i < store->num_orders(); ++i)
        oss << i << ") " << store->order(i) << "\n\n";
    oss << "</tt>";
    set_data(oss.str());
    set_msg("");
}

void Mainwin::on_view_customer_click()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Customers</b></big><tt>\n\n";
    for (int i = 0; i < store->num_customers(); ++i)
        oss << i << ") " << store->customer(i) << "\n";
    oss << "</tt>";
    set_data(oss.str());
    set_msg("");
}

void Mainwin::on_insert_peripheral_click()
{
    std::string peripheral = get_string("Name of new peripheral?");
    double cost = get_double("Cost?");

    Options option{ peripheral, cost };
    store->add_option(option);

    on_view_peripheral_click();
    set_msg("Added peripheral " + peripheral);
}

void Mainwin::on_insert_desktop_click()
{
    on_view_peripheral_click();
    int desktop = store->new_desktop();
    while (true) {
        std::ostringstream oss;
        oss << store->desktop(desktop) << "\n\nAdd which peripheral (-1 when done)? ";

        int option = get_int(oss.str());

        if (option == -1) break;
        try {
            store->add_option(option, desktop);
        }
        catch (std::exception & e) {
            Gtk::MessageDialog{ *this, "#### INVALID OPTION ####\n\n" }.run();
        }
    }
    on_view_desktop_click();
    set_msg("Added desktop " + std::to_string(desktop));
}

void Mainwin::on_insert_order_click()
{
    on_view_customer_click();

    int customer = get_int("Customer?");
    if (customer == -1) return;

    int order = store->new_order(customer);

    on_view_desktop_click();
    while (true) {
        int desktop = get_int("Desktop (-1 when done)?");

        if (desktop == -1) break;
        store->add_desktop(desktop, order);
    }

    on_view_order_click();
    set_msg("Added order " + std::to_string(order) + " for $" + std::to_string(store->order(order).price()));
}

void Mainwin::on_insert_customer_click()
{ 
    std::string name = get_string("Customer name?");
    if (name.size()) {
        std::string phone = get_string("Customer phone (xxx-xxx-xxxx)?");
        std::string email = get_string("Customer email (xxx@domain.com)?");

        Customer customer{ name, phone, email };
        store->add_customer(customer);
    }
    on_view_customer_click();
    set_msg("Added customer " + name);
}

void Mainwin::on_new_store_click() {
    delete store;
    store = new Store;
    filename = "untitled.elsa";
    set_data("");
    set_msg("New store created");
}

void Mainwin::on_open_click(){
	 Gtk::FileChooserDialog dialog("Please choose a file",
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_elsa = Gtk::FileFilter::create();
    filter_elsa->set_name("ELSA files");
    filter_elsa->add_pattern("*.elsa");
    dialog.add_filter(filter_elsa);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename(filename);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);
    int result = dialog.run();
    if (result == 1) {
        try {
            delete store; store = nullptr;
	    filename = dialog.get_filename();
            std::ifstream ifs{filename};
            store = new Store{ifs};
            //bool b;
            //ifs >> b;
            if(!ifs) throw std::runtime_error{"File contents bad"};
	    on_view_customer_click();
	    set_msg("Loaded" + filename);
        } catch (std::exception& e) {
            std::string err = "Unable to open store from " + filename + " (" + e.what() + " )";
            on_new_store_click();
            set_msg("<b>ERROR:</b>: " + err);
            Gtk::MessageDialog{*this, err, false, Gtk::MESSAGE_WARNING}.run();
         }
    }

}


void Mainwin::on_save_click(){
	
        try {
            std::ofstream ofs{filename};
            store->save(ofs);
            if(!ofs) throw std::runtime_error{"Error writing file"};
        } catch(std::exception& e) {
            std::string err = "Unable to save store to " + filename;
            set_msg("<b>ERROR:</b> " + err);
            Gtk::MessageDialog{*this, err, false, Gtk::MESSAGE_WARNING}.run();
        }

}
void Mainwin::on_save_as_click(){
  Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_elsa = Gtk::FileFilter::create();
    filter_elsa->set_name("ELSA files");
    filter_elsa->add_pattern("*.elsa");
    dialog.add_filter(filter_elsa);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);


    dialog.set_filename(filename);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);
    int result = dialog.run();
    if (result == 1){
	filename = dialog.get_filename();
    	on_save_click();
	}
}


void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("ELSA");
    auto logo = Gdk::Pixbuf::create_from_file("macrohard.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 1.2.1");
    dialog.set_copyright("2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = { "Jason Shamayev" };
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "Logo by Jason Shamayev, licensed under Macrohard",
        "Robot by FreePik.com, licensed for personal and commercial purposes with attribution https://www.freepik.com/free-vector/grey-robot-silhouettes_714902.htm" };
    dialog.set_artists(artists);
    dialog.run(); 
    set_msg("");
}

void Mainwin::on_easter_egg_click() {
    Customer c{ "Bugs Bunny", "817-ACA-RROT", "bugs@loony.tunes" };          store->add_customer(c);
    c = Customer{ "Elastigirl", "817-STR-ETCH", "helen@incredibles.movie" }; store->add_customer(c);
    c = Customer{ "Tuck and Roll", "817-UFI-RED2", "circus@bugs.life" };     store->add_customer(c);
    c = Customer{ "Tiana", "817-NOG-RIMM", "princess@lily.pad" };            store->add_customer(c);

    Options o{ "CPU: 2.6 GHz Xeon 6126T", 2423.47 };         store->add_option(o);
    o = Options{ "CPU: 2.4 GHz Core i7-8565U", 388.0 };      store->add_option(o);
    o = Options{ "CPU: 2.2 GHz AMD Opteron", 37.71 };        store->add_option(o);
    o = Options{ "CPU: 300 MHz AM3351BZCEA30R ARM", 11.03 }; store->add_option(o);
    o = Options{ "CPU: 240 MHz ColdFire MCF5", 17.33 };      store->add_option(o);

    o = Options{ "2 GB RAM", 17.76 };                        store->add_option(o);
    o = Options{ "4 GB RAM", 22.95 };                        store->add_option(o);
    o = Options{ "8 GB RAM", 34.99 };                        store->add_option(o);
    o = Options{ "16 GB RAM", 92.99 };                       store->add_option(o);
    o = Options{ "32 GB RAM", 134.96 };                      store->add_option(o);
    o = Options{ "64 GB RAM", 319.99 };                      store->add_option(o);

    o = Options{ "0.5 TB SSD", 79.99 };                      store->add_option(o);
    o = Options{ "1 TB SSD", 109.99 };                       store->add_option(o);
    o = Options{ "2 TB SSD", 229.99 };                       store->add_option(o);
    o = Options{ "4 TB SSD", 599.99 };                       store->add_option(o);

    o = Options{ "1 TB PC Disk", 44.83 };                    store->add_option(o);
    o = Options{ "2 TB Hybrid Disk", 59.99 };                store->add_option(o);
    o = Options{ "4 TB Hybrid Disk", 93.98 };                store->add_option(o);

    int desktop = store->new_desktop();
    store->add_option(0, desktop);
    store->add_option(9, desktop);
    store->add_option(14, desktop);

    desktop = store->new_desktop();
    store->add_option(1, desktop);
    store->add_option(7, desktop);
    store->add_option(17, desktop);

    desktop = store->new_desktop();
    store->add_option(5, desktop);
    store->add_option(7, desktop);
    store->add_option(15, desktop);
}
// /////////////////
// U T I L I T I E S
// /////////////////


std::string Mainwin::get_string(std::string prompt)
{
    EntryDialog ed_string{ *this, prompt };
    ed_string.run();
    return ed_string.get_text();
}

double Mainwin::get_double(std::string prompt)
{ 
    try {
        return std::stod(get_string(prompt));
    }
    catch (std::exception & e) {
         Gtk::MessageDialog{*this, "ERROR: Invalid double"}.run();
        return -1.0;
    }
}

int Mainwin::get_int(std::string prompt)
{
    try {
        return std::stoi(get_string(prompt));
    }
    catch (std::exception & e) {
         Gtk::MessageDialog{*this, "ERROR: Invalid int"}.run();
        return -1;
    }
}

void Mainwin::set_data(std::string s)
{
    data->set_markup(s);
}

void Mainwin::set_msg(std::string s)
{
    // Display the collected status on the status bar
    msg->set_markup(s);

}



