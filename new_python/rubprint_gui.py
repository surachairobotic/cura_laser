from PyQt5 import QtCore, QtGui, QtWidgets
from printer import *

def pWidgets(wdgt, func=None, font=None):
    if not font:
        font = QtGui.QFont("Arial", 16, QtGui.QFont.Bold)

    p = wdgt
    p.setFont(font)
    '''
    if isinstance(p, QtWidgets.QLabel):
        p.setAlignment(QtCore.Qt.AlignCenter)
        print(type(p))
    '''

    method = getattr(p, "setAlignment", None)
    if callable(method):
        p.setAlignment(QtCore.Qt.AlignCenter)
        
    if func:
        p.clicked.connect(func)
    return p


class PageWindow(QtWidgets.QMainWindow):
    gotoSignal = QtCore.pyqtSignal(str)

    def __init__(self):
        name = 'PageWindow'
        print(str(name + " 1"))
        super().__init__()
        print(str(name + " 2"))
        self.w = 640
        self.h = 480
        frm = QtWidgets.QFrame()
        self.setCentralWidget(frm)
        self.setFixedSize(self.w, self.h)

    def goto(self, name):
        self.gotoSignal.emit(name)

class FirstWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.status = ["Card init : ----", "Laser init : ----", "Base init : ----", "G-Code init : ----"]
        self.font = f
        self.initUI()
        self.printer = p
        self.initEnvProcess()

    def initUI(self):
        self.setWindowTitle("First")
        self.UiComponents()

    def gotoLaser(self):
        self.goto("laser")

    def UiComponents(self):        
        vLayout = QtWidgets.QVBoxLayout()

        for msg in self.status:
            label = pWidgets(QtWidgets.QLabel(msg))
            vLayout.addWidget(label)
        
        self.nextButton = pWidgets(QtWidgets.QPushButton("continue ..."), self.gotoLaser)
        vLayout.addWidget(self.nextButton)

        wdg = QtWidgets.QWidget()
        wdg.setLayout(vLayout)
        self.setCentralWidget(wdg)
        
    def initEnvProcess(self):
        self.gcode_file = "C:/cura_laser/python/ear/layer_0.gcode"
        self.status = self.printer.init(self.gcode_file)
        self.updateStatus()
        
    def updateStatus(self):
        wdg = self.centralWidget()
        count = wdg.layout().count()
        for i in range(count-1):
            wdg.layout().itemAt(i).widget().setText(self.status[i])

class LaserWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f

        name = 'LaserWindow'
        print(str(name + " 1"))
        super().__init__()
        print(str(name + " 2"))
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Laser")
        self.UiComponents()

    def goToMain(self):
        self.goto("main")
    def goToBase(self):
        self.goto("base")
    def getLaserState(self):
        #self.label_getLaserState = 'Laser state : ' + str(self.printer.laser.checkState())
        self.label_getLaserState = 'Laser state : ' + str(True)
        self.labelWdgt.setText('Laser state : ' + str(True))

    def UiComponents(self):
        #self.nextButton = QtWidgets.QPushButton("nextButton", self)
        #self.nextButton.setGeometry(QtCore.QRect(5, 5, 100, 20))
        #self.nextButton.clicked.connect(self.goToBase)

        self.btn_getLaserState = pWidgets(QtWidgets.QPushButton("getLaserState"), self.getLaserState)
        self.label_getLaserState = pWidgets(QtWidgets.QLabel("NaN"))

        self.btn_sleep = pWidgets(QtWidgets.QPushButton("SLEEP"), self.getLaserState)
        #self.btn_sleep.clicked.connect(self.printer.laser.setState(0))
        self.btn_standby = pWidgets(QtWidgets.QPushButton("STANDBY"), self.getLaserState)
        #self.btn_standby.clicked.connect(self.printer.laser.setState(1))
        self.btn_on = pWidgets(QtWidgets.QPushButton("ON"), self.getLaserState)
        #self.btn_on.clicked.connect(self.printer.laser.setState(2))
        
        self.btn_quit = pWidgets(QtWidgets.QPushButton("QUIT"), QtCore.QCoreApplication.instance().quit)
        self.btn_next = pWidgets(QtWidgets.QPushButton("NEXT..."), self.goToBase)

        vLayout = QtWidgets.QVBoxLayout()

        hLayout = QtWidgets.QHBoxLayout()
        hLayout.addWidget(self.btn_getLaserState)
        hLayout.addWidget(self.label_getLaserState)
        self.labelWdgt = hLayout.itemAt(1).widget()
        vLayout.addLayout(hLayout)

        hLayout = QtWidgets.QHBoxLayout()
        hLayout.addWidget(self.btn_sleep)
        hLayout.addWidget(self.btn_standby)
        hLayout.addWidget(self.btn_on)
        vLayout.addLayout(hLayout)

        hLayout = QtWidgets.QHBoxLayout()
        hLayout.addWidget(self.btn_quit)
        hLayout.addWidget(self.btn_next)
        vLayout.addLayout(hLayout)
        
        
        wdg = QtWidgets.QWidget()
        wdg.setLayout(vLayout)
        self.setCentralWidget(wdg)

class BaseWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Base")
        self.UiComponents()

    def goToLaser(self):
        self.goto("laser")
    def goToGCode(self):
        self.goto("gcode")

    def UiComponents(self):
        #self.nextButton = QtWidgets.QPushButton("nextButton", self)
        #self.nextButton.setGeometry(QtCore.QRect(5, 5, 100, 20))
        #self.nextButton.clicked.connect(self.goToGCode)

        vLayout1 = QtWidgets.QVBoxLayout()
        vLayout1.addWidget(pWidgets(QtWidgets.QPushButton("HOME")))
        vLayout1.addWidget(pWidgets(QtWidgets.QPushButton("JOG +")))
        vLayout1.addWidget(pWidgets(QtWidgets.QPushButton("JOG -")))

        # change speed
        vLayout2 = QtWidgets.QVBoxLayout()
        vLayout2.addWidget(pWidgets(QtWidgets.QPushButton("SPD +")))
        vLayout2.addWidget(pWidgets(QtWidgets.QPushButton("SPD -")))
        hLayout2 = QtWidgets.QHBoxLayout()
        txtBox1 = pWidgets(QtWidgets.QLineEdit())
        txtBox1.setValidator(QtGui.QIntValidator())
        txtBox1.setMaxLength(2)
        hLayout2.addWidget(txtBox1)
        hLayout2.addLayout(vLayout2)
        vLayout3 = QtWidgets.QVBoxLayout()
        vLayout3.addLayout(hLayout2)
        vLayout3.addWidget(pWidgets(QtWidgets.QLabel("current position = ???")))
        
        vLayout4 = QtWidgets.QVBoxLayout()
        vLayout4.addWidget(pWidgets(QtWidgets.QPushButton("SAVE")))
        vLayout4.addWidget(pWidgets(QtWidgets.QPushButton("<-- BACK"), self.goToLaser))
        vLayout4.addWidget(pWidgets(QtWidgets.QPushButton("NEXT -->"), self.goToGCode))
        vLayout4.addWidget(pWidgets(QtWidgets.QPushButton("EXIT"), QtCore.QCoreApplication.instance().quit))
        
        hLayout = QtWidgets.QHBoxLayout()
        hLayout.addLayout(vLayout1)
        hLayout.addLayout(vLayout3)
        hLayout.addLayout(vLayout4)

        wdg = QtWidgets.QWidget()
        wdg.setLayout(hLayout)
        self.setCentralWidget(wdg)

class MainWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f

        name = 'MainWindow'
        print(str(name + " 1"))
        super().__init__()
        print(str(name + " 2"))
        self.initUI()
        self.setWindowTitle("MainWindow")

    def initUI(self):
        self.UiComponents()

    def UiComponents(self):
        self.searchButton = QtWidgets.QPushButton("", self)
        self.searchButton.clicked.connect(
            self.make_handleButton("searchButton")
        )

    def make_handleButton(self, button):
        def handleButton():
            if button == "searchButton":
                self.goto("search")
        return handleButton


class SearchWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Search for something")
        self.UiComponents()

    def goToMain(self):
        self.goto("main")

    def UiComponents(self):
        self.backButton = QtWidgets.QPushButton("BackButton", self)
        self.backButton.setGeometry(QtCore.QRect(5, 5, 100, 20))
        self.backButton.clicked.connect(self.goToMain)

class GCodeWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f
        self.initUI()

    def initUI(self):
        self.setWindowTitle("GCode")
        self.UiComponents()

    def goToProcess(self):
        self.goto("process")

    def UiComponents(self):
        self.nextButton = QtWidgets.QPushButton("nextButton", self)
        self.nextButton.setGeometry(QtCore.QRect(5, 5, 100, 20))
        self.nextButton.clicked.connect(self.goToProcess)

class ProcessWindow(PageWindow):
    def __init__(self, p, f):
        super().__init__()
        self.printer = p
        self.font = f
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Process")
        self.UiComponents()

    def goToMain(self):
        self.goto("main")

    def UiComponents(self):
        self.nextButton = QtWidgets.QPushButton("nextButton", self)
        self.nextButton.setGeometry(QtCore.QRect(5, 5, 100, 20))
        self.nextButton.clicked.connect(self.goToMain)

class Window(QtWidgets.QMainWindow):
    def __init__(self, p, parent=None):
        super().__init__()
        self.printer = p
        self.font = QtGui.QFont("Arial", 7, QtGui.QFont.Bold)

        self.stacked_widget = QtWidgets.QStackedWidget()
        self.setCentralWidget(self.stacked_widget)

        self.m_pages = {}

        self.register(FirstWindow(self.printer, self.font), "first")
        self.register(MainWindow(self.printer, self.font), "main")
        self.register(SearchWindow(self.printer, self.font), "search")
        self.register(LaserWindow(self.printer, self.font), "laser")
        self.register(BaseWindow(self.printer, self.font), "base")
        self.register(GCodeWindow(self.printer, self.font), "gcode")
        self.register(ProcessWindow(self.printer, self.font), "process")

        self.goto("first")

    def register(self, widget, name):
        self.m_pages[name] = widget
        self.stacked_widget.addWidget(widget)
        if isinstance(widget, PageWindow):
            widget.gotoSignal.connect(self.goto)

    @QtCore.pyqtSlot(str)
    def goto(self, name):
        if name in self.m_pages:
            widget = self.m_pages[name]
            self.stacked_widget.setCurrentWidget(widget)
            self.setWindowTitle(widget.windowTitle())

class A():
    def __init__(self):
        super().__init__()
        self.a = 10
    def get_a(self):
        return self.a

class B(A):
    def __init__(self):
        super().__init__()
        self.b = 9
    def get_b(self):
        return self.b

class C(B):
    def __init__(self, k):
        super().__init__()
        self.c = 8
        self.kk = k
        
    def get_c(self):
        return self.c
    def plus_a(self):
        self.a = self.a + 1

if __name__ == "__main__":
    import sys
    
    z = A()
    x1 = C(z)
    x2 = C(z)
    x3 = C(z)
    print(x1.kk.a)
    print(x2.kk.a)
    print(x3.kk.a)
    x3.kk.a = 77
    print(x1.kk.a)
    print(x2.kk.a)
    print(x3.kk.a)

    
    app = QtWidgets.QApplication(sys.argv)
    
    p = Printer()
    
    w = Window(p)
    w.show()
    sys.exit(app.exec_())