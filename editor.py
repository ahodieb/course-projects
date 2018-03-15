#!/usr/bin/env python
__author__ = 'Abdallah Hodieb'

import pygtk,gtk,sys
import masm

class ManoAsm(object):
    def window_destroy(self,widget,data=None):
        sys.exit(0)

    def window_destroy_event(self,widget,data=None):
        pass


    def btn_open_clicked(self,widget,data=None):
        dialog = gtk.FileChooserDialog("Open..",
                               None,
                               gtk.FILE_CHOOSER_ACTION_OPEN,
                               (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                                gtk.STOCK_OPEN, gtk.RESPONSE_OK))
        dialog.set_default_response(gtk.RESPONSE_OK)

        filter = gtk.FileFilter()
        filter.set_name("All files")
        filter.add_pattern("*")
        dialog.add_filter(filter)

        r = dialog.run()
        response = dialog.run()

        if response == gtk.RESPONSE_OK:
            f = dialog.get_filename()
            self.textview1.get_buffer().set_text(open(f).read())

        elif response == gtk.RESPONSE_CANCEL:
            print 'Closed, no files selected'

        dialog.destroy()

    def btn_asm_clicked(self,widget,data=None):

        b = self.textview1.get_buffer()

        start = b.get_start_iter()
        end = b.get_end_iter()
        
        asm = b.get_text(start,end).split('\n')
        # print asm

        a = masm.Assembler(asm)
        a.generate_symbol_table()
        a.assemble()

        self.textview2.get_buffer().set_text(a.str_output()[0])
        print a.str_output()[0]

    def __init__(self):
        try:
            builder = gtk.Builder()
            builder.add_from_file('gui.glade')
        except:
            sys.exit(1)

        self.window = builder.get_object('MainWindow')
        self.window.set_title('Mano Assembler - By Abdallah Hodieb')

        self.btn_open = builder.get_object('btn_open')
        self.btn_asm = builder.get_object('btn_asm')

        self.textview1 = builder.get_object('textview1')
        self.textview2 = builder.get_object('textview2')


        builder.connect_signals(self)


if __name__ == '__main__':
    app = ManoAsm()
    app.window.show()
    gtk.main()
