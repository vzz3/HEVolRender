// main
#include "PerformanceTest.hpp"
#include <string>
#include "UArbBigInt.hpp"
#include "SArbBigInt.hpp"
#include <chrono>

using namespace ppvr::math;

void PerformanceTest::fromString() {
	
	std::cout << math::UArbBigInt::fromString(  "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16).toStringHex() << std::endl;
	/*
	std::string numStrIn("1234");
	math::BigInt a = math::BigInt::fromString(numStrIn, 10);
	std::string numStrOut = a.toStringDec();
	std::cout << "In: " << numStrIn << ", out: " << numStrOut << std::endl;
	*/
	
	/*
	math::BigInt test(0);
	uint8_t result, rest;
	test.divTwoWords(0x36, 0xa5, 0x8e, &result, &rest);
	std::cout << "0x36a5 / 0x8e = result: " << std::to_string(result) << " (expected: 98 / 0x62) , rest: " << std::to_string(rest) << " (expected: 73 / 0x49)" << std::endl;
	
	uint64_t bigIntRes = (math::BigInt::fromUint64(0xDA96ull) / math::BigInt::fromUint64(  571)).toUint64();
	std::cout << "result: " << std::to_string(bigIntRes) << " (expected: 98)" << std::endl;
	*/
	
	auto startTime = std::chrono::high_resolution_clock::now();
	
	math::UArbBigInt devTestRes = math::UArbBigInt::fromString(    "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) / math::UArbBigInt::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16);
	math::UArbBigInt devTestResReference = math::UArbBigInt::fromString(  "123456789abcdef000000000000000123456789abcdef0", 16);
	if(devTestRes == devTestResReference) {
		std::cout << "SUPER!" << std::endl;
	} else {
		std::cout << "ERROR!" << std::endl;
	}
	
	//math::BigInt test = math::BigInt::fromString("235131727369793598590237927764327204907148418164945334929209808908609764248872000066242323468863555199676594920212602965453323155296135730823798195269211664656099299342438661381834514623279041772166444954511708391015722895874195656374613822945545696494212556595774802101190576031720894607150635820520441402088848948291688752806902757547248673629269017502396086768556246929722149748128651974902900938948631946706677657087442335326305793283786426587137880294841762641262458951011187343624314169099408722061144065682400560742207893177229024368858782308151526955442479388997380747719815030513808467089362737612016474932458928560286135649656702635257518527949842171790395430352547097705094761396425013402456710753306722925975887903774200064103107061402842408845112258286395675238500043419535336328644685762659179188142594033233156760569619145444465447119442688589567820637051214115321669253706115446541877223495734908272788181245756766495605512497239521194937129256710525896692858013722560872034974732710298814928778564509164468751299785340791354413530822178307488910138304885796089942578324626341955013078468012460114858057616657944434333386298801618014952688549274444450810384598514318629481339200379589959042143710511819559346097571837578418992641528678028803511447779225621244515282709627042397241577409787670473279562947082775848563907727814574077009850724835573310617540815143410753661112735043763870375303636993551026559182999191036332848109084080430165453534585373784117420799991830889543349711955956511387781767167166558251200214303288610875881328672237926542407866799220327717600541521483167657381853198494047913317596950171449779368491036552615604095603909926737193304440270251797886513083560076145186057646246750775966029859016224453850881200415764417624796017170145559969226939914712837705215211114208809592042864252752640508755097674077983549961394964778246870917849626235687780256258054588240610995575856784322305771312238407910690916012250979209774124529439990662675073688522067061674380007088044331379846406692559602362083496956283454433672958960737513637429981090113699848642370960987654051063877822437864450347391956595331894276287417347769356273160822645733236415330368918822403282708741717202440995430205250513050504295670702141723083635172068134075917891066238170095449883778971795843637916631459957353184455966473607818636174808325159356110640929994928825770439680638900428958097816165209311084010101686090756926710075449289286207428643356148197622537962729318254120464476353572656839008390430652006387671125636879985744941882842779910558804132922234038850919197621848124525208062078273571816565333815097314993616362734097194249480359242239397825780911267546180569994257932232202271461300345307317936111504463199865920790727756586682812729702793661755600209930787118342298868172652142002637209509078286736394494347346290762876900539130716361413953818834955789474666983527429947056916317790694436312091308015495445099963986259228979221228764704289050409272057235454644247446695849989070955969232556131053321635636028873677452434730203701902154863053692232773031141376117441957681274913925529133143241731791342228850618659184766182619280375921753504754286917298136903375724012093755484378577197380053186169130561118645633062090298103084160893725886070653916245881559546369767203341749468730373276804944526622731466162623926549663275477114180116381878721708638034362613218264636884178855020977780033452309013338338116866502189353635217369544490459289786477984127554671061454436975190573363075993401195349111426632164645313893619920424065492912100165527764934954237003248305721997238554131583372353703655794355302397290516465877933055077658045057560335352127561770461827924106182125292721991482626877503036893503148652437332534425160992353895748580149847973237161904318875434198084422432988782697569411945521132233626266207207325171070629399224815817118722076998850034507615226857402452330641138741159202708648823865307480109747243923528988679124314806545132863082244074420311922923650460395577274537129971908526099346206861941864951662813406750780044715000769492819948479148638778930817476597531160475805551565577054869253717516609228100401479965445551554301320968264018215358889179384480210935889662957745938765579694931865914781505472477288406192206518964526074775890704026178328167052222857914996999779020426571879601905890284802264746623834227209831942601903379468339309623507706613113295393156296613248226611679289175281777154746535195232001135902202461281276826273565581440628505334333853478501098064087122527902740195505207970415320682292812689389691295022917075199395381363548789616686357494232028276587646355923419037622530303282118724719870762362437476567935558443332980036918516697001712716333608185129700588362255711570595021405471331878061346988931715519710770372594524210095327034922678364167020080882895082315073055160283845175193717226198291512002872623593093417180386859868752333731841363785254383602622409683137512107248639162294934435402101273907941443828010725985684404258694327165343259094837588664250451872665448071837189735666559102572420426040952101626854482347358141921781416549632550202350751698922136806830592376099788557081841661640637790123488919674676523529487034661870510635466975092584587976022332542662116032413123371722313846241219453559872474199429343427451246513516870518927235871740752893659307659266815227731652755694628594224915766290147551567965928247812004310817173443972325959496945195439393512382028328526351136319587630773111489980584812436156888017756305520001229737203415218465707772221159530942060703396301006455581777062910246325145817793314366922546886953791049498123699442109431670476520383386929165159425161760231111220776472636937012609900160024190417120981673868749914924825233519671802606078433638782921787270841713641832319402799546989564976975436545017658500565470342497257963436077847402657400509902991010584087902234306632259818606677882302317837916061067593530730297323898218182142629739503472415805441787381366541179954030135861290561200735222823289927862514609159832554516045268126522359344866480932632090180439158728653760291053169256956763465864989010464217615925236175550791689473148829016141106331870185919410551442771906094610995312770461972268642330441413338175913211834676909385335323383387678370845296128845203167315552901919597802327750697034630474963769391057059111351606032679515404452107187673487961525614716362698673555449415255311586782600390974347889512434586216438570456127511475977426688379718598481495821475546566771024695420191616824818777628193460997159677710247115603938755118004316060858872839651908015075372275475102756283920431551783913144356712015767698356337679487943657192284254598838308831047533957057313593354099313663297790803287370990347859075450515438372129211648406251352185122677743030805791941565940220508891195603879705144778562234105805997228789200762557717640194781572344555261524944796235859277873654613181443042053643116988913652891169294736600373143073440549346054673324178527660357158463727180516311016224808906386702873748502846185503258467818695704690307389326365353409161210672135177984403874844673041935174164363057696892926231273698290368099843099770735891861323222394865761454283252219407555271831912222149644623002345418832352723877264119479125636442106965258394120258356171994757071625254928181117564071551565072413983427678066302973800501234084337419947680059093167344072661617808178348635901476543378834233192245905860300628403547052039132947915833579792137016644056578455804798271983792538825620155478289388646959577296350015602938609778302582048339131865331801384396531882520553786404737587101700780199820814484586571989181941033411435795632278117666698821409471316940052055753111026411032154985014903037435619759672050067221628089300013832862226397515444440594127840907744334825730493081295414822720030727458461657781930273763340879165157298352939594013063703886256174451347114439292678955787011602073598524382968813039537611686030602254037135409562747709791440666086882645295277603505649417488294937055584421977494562454499193608592372225860884836289945961308651320126998406278833034830510214995171382964992406106094415135068938139266359688688193215099398333597625087928882257649392444104511867944687867784975759352336717597403490031773448628647396070240256041363130117495488958354675370230619493781867565808074030912282446247871538986085144797438869995690996458355678694700388594570791212356689163761772711053303630417310000462636603694761287247843958035420380909909709998309489601821279610391337645117776196170498083870242598177149120198945985961887718760061358007940161865655000918634871627779015097123224479681615319480987751327419883528981000187650321034115904138411374134807315364004701273365175486423486601490351055977553931449342783183598219931664778332456139402190675165225780258995657860356526821984945762644975027288177622471188984287286569576281002519745044866772569744472160399392199251879491026094573842969998648534841021798994595691439751278598712868117700282114705747352076694575970108199590129168528792978656241293315348774232445223431350140491658746167380148287025077914377965121565338642708739499091876104010843925439957311626302787480971835021690038994978768443916415116318408938473141820325118420942415263113711529959779218250707018842010821159987726569562710723706152534784051515027149237439327747494564380263421932628374007771939247859855661221209093926540750699751890165833199147016190781230022918939552396828884348717483767891060638823183679223001606177169700170849406077332326245761413530614449100547995755482566211564715864428419617583478827799035147340093916276320404663630723320197095450542058761774781873276018366582029234940369910061644929886830776426210802791915140250984282690448609966398921070658726416660745914561167231377562017066582747016666476047219099160668822190371009273632102734264240170863201854790221031286622177398534831901307522797026611376407225079002215773201948544872906174985013010529882515319025353837392574960505916767771531959579873531370906737752931233157737181761633751031553857529289928819488425702466226633259691727081394795284219117296688528300582247722834406955903563537033908076459759583480662044008261840754731475468509807104411032914439135278402552227858785823206623166357959547302448923687756075724887610045766146566994402164819212857643226951834183509586250378607526456967418488270428192765963716860258046173708267754976678902514682608964398353026663364871271334502804010123271186108735400292520005589092057751460440529767435133642926799901491747874406618050460590471282887050867957927392928166673160750149266278097870029346450227909035081311417332900385586664215533688578575023461958122086100168406359925341637943391094521992887497835126812867160092838692561811863683145806457919902096987308538920021109382459437399553886773570375719728160436165049527136131486918579384599210210960893176821684472303938151472429664239842570154160958415314446489106820897983733387712242368810902724914532619550148957455531679313611739075156392879212806685092394612180495865744390971825215707808122744384170684527328523620725223388751446259341474290638199708574757029558606873610144696493130728167520895022181113492604415287226815978641055486653509337312844992231880917337503470595903107556830664378337387835226745623696943362527728272480683852317713504994502477406806712300916252484244641098402727737493408177230359405321656289293710563766526866420059956811702129018726049132104133091834698984984739606228612321777202942751479270662482558114021223481431431072139166016334921640815454157318059144145679474862724375713966801818900132293310509808718144265858878546818663406500491614278322398093358593894890659807928207132752586733660882940209665639225388905130496238142229825541862035206127801473863192714429428944517911451792996591592537346826502929136655783140561665260934654827897939746442990362338855012246699045039566163507657167167934533069365316604373451195486488887289485303355403745220508186323108710400063916923564226634187717143125508910341654595985756837094122646690316877697368501233819325911869971520945990208918258379183769634696721861948570102865706443749816812696333481493369944686820956371350038307978515072643148480080208903386565114535729052641730568652904695146196130621251545640665855637075057794087325457440667196432773702702070039558923026383352166871584893275636323188185980273215370103788924139371105483641560399158493130350713214447196727771580688853162469414572156687879320454623294493030412689757052890265830924418229418397389902710405405543519240459762455722733895038826259833595802013039282073883216668776647814050703999198932243199629314956261041100765513202067741186511606364013205876005301968360020797722496936119458024397394218163779322579925621101352910651933684826245190921430593150452488948049706175323344565093177146694802407595128203084217524289197684095787657295050941524973083194701806682757964238027089302235672204421963358069289932460205739304335176101364203312631297477727697952251091573611514423116966893421668189650270200771589153792501677758454236090790232300524198619528267340217972593073806308044251667314687223099491372766391803099688589900005174209003566644123617673958250233675467270989355075854464516555980735954167478418379041069058678452632138556269784196986097422548215997592177754692811076363454438380633008206440573054003152606605109408200352193304335857838128932010196735017411994465180542750533025041591879579449904990675996955440343656002965053745978338715328910178798943271394211786168904887974652539097434567775113859446561094776504066184504291398317567150191140577107728271567171432197188335213209129926707415352162543057529539385830245522734659654799981031643176782003387655121329298096085235276820546113288719260332963340430295940646372885123213044328960834400099356504711158310625981915880619554576064328070569045479090458705923173172054858775749238618839447943088452088690685762574929501416820768591165137835776010088147092375288206422990475656322825704647064080170113438565358104744621346550356857975674978089680023894144579111378004007978127423329841141794436786998476095700398884215744019867898249695623687946439420237727403335886715655780069878643259403546612086187093251217508648295018052219485874321964393775406438386964551978139658704614138195581642305164051912783658277767991884944107479763810648376727788807244362433964211774848250194993286737662129286212739983588659635556843292182729092485947894919264985869800551328479277164845149047249681294444684870883789467798132704821321213212568553038985406405286377958168158993935578110934317718770526773001743625590630244661463774170852423744935339827273116729868808392806089609230475030262669535637953331111117024766025102239538171650651256252492597441202594968827395315432284893641604334362991641810422246382972292018693644167521248112552129642255902609979813337197012389236090264376177519634017744248991870258986339993078504748490791688054076821192225573131067030005346437738550314002046474740186425717730190702877641772567301598534523237689021473787832014704324931454624365709624541868982452288181921251455354923248722214589993883769247750088484321183754030868868136394035871103245291695694091678972243310899856636575359498750305726553177782265893365511610522404619221117715910206234770004649000158288753606003783278712957971390063672685377612374846072589112660624102538421423942953379790412091870502254281665825228323272817085856453425310340562602610817504185190066656400120118342192104042377354105820861729542726857243890204628140196010684896364633751787152822890588862961805080953260777304558547878600015182065451661619128702160350636204034040451673120580443624692706662966297238332805983788645124545331489261473636230943446019090993121103219764654147446068503351061948200532174477970453618307043246707814359558704864097836878669771321645695901219995518264710949918350048864010872904042700494813508188952554104545520381750137714804442922498309335173459937235379478192738565842296572774696203057991719503497561972893260429638433347713826345220812836213999041476551890341165655508882409476507874447865471196569034890150056758979868454031697589848958831614593022402758561522206027362299900951312859399938216277420852515787559239698471768055218072916186760584787307356188279706960468022655832106168041090525950858600096000963799056765317438597543301170210930782139852610655318746592547009620093212081547161494259405995543467865768792676252801907116899641580888179721105563023711652646193045849011148466651728265800429762096999069606826596876631206685145298894757495143186168090942242394169253922597929436995189573156795380662969605566891639447305828700914742566365548068603890985317847778234048909380718524464281907493046621496295004211969182269103264886360162829568008776013182671987420731859640033591353005096073147828623133684747051527544965208017518040351197900521173471794528754695668369586640699357788548864485226792025710523296502052254304936870636372444170166126328185769364601488847271361788658245938342656747812150605770739222554045566999670422961415701392330044351421466973793274538288007937803252828719517505564614223377265169586427736526883064040657965053098592652651266035649533644838251697479030491804460922419147566816623308692960203894565670069401410691344479111684008105567240210273981369642601651608514020677619707504563656220934220962152682895429197367129945727561821499740925088159520622206543789031058995540854254446361050229003293958943073796302070538180624561928355995566181178497410757517433038222792159764992957400225845617774670376915312845638218532429175409906049924643616986154754554779101577918283899919347502311180697693323762222392685498256733515819298261352295767759721383793903960574870029761986240029489978773653269273385189371707270546542588006618959974931294348785881178733588297672836261301402096770892358589264262250838006108114448003292976173685858501814631309976173579886623099064815648913061181925644157776999069726502975892132857391170215023610174403655565615137238637135319935122566369942697863454090417018554445147292737923908260529363323635476486378277807692938241388583929851174290724374857461421278572832153559668723901842265467565860273532421888957546928891918038991550487984262383877765483680342988769245239677066615672436692122267623118106074622291078337740429994908609618870633223075811831439138494070182381889705877426823774114688871028926224049201442878376147339958918356952327863135517148055790535408820862452459802370789442926695182830544034190214487140671809524178991840024650002497636900630928805395879666149852689508266808330228741711342096849197284569096716800954670753754999238946992858452551049647274500862238658980721516199655673254563224684053464834903088462778566888068495618490636724383785527882938573486017379734081149155681393187191071861076488526677326486064717806682353577151499244692325356411633762757487460034108923641524869423105593254278604634497937688192971499637957056082035394865398722451453775461022178038868050654078426058043860250228775227730715781442871271565848406283233070981064793977810892624324238081311963260958766726794869666388440707661175132179964386830465631441998550073857304277593713931999324367940869560342712543070153249444855948792447605379484828506247570490046098191848844205599509422835433157118878943733216471834207629792928018236352613944948523089021743090825289477119521269208970227627186905910474201867027760320177100521125557220212830436151331883602020402363007701423825057272628319601708679093703600875782794137718453122872630901374778783753860790844541753547547479135500945982266818535359438269570414482856035649957981226396134516887267352371441996470443033621416080449844789299028720233744985159721741857583541214116347309860429255749090976975792107406933932430886798869630138778678830246871782205041076497048052502094275427573913857957047447615309791380629894787399872300641889522633521065317039435709316852537166016997768360319046027385462334903041129329946489316779006519950820822213578319577064411393697057441970241918355236609923324843207341113633024644829250822653688959839296615354426781509152566941944578332686900669298378609148352499594716306071473928517633120561149138120517283455239263777149161609836471210755806333047528836891032254896286380858475160047846758203553968523407112969665193148671078439617477173044252087307009135295325144827340080377788638481780915409602527742381574960982368764096836962550429551369078657366081683802708236786934375455851631746810733547772987923951856110801260384429761300964340447769629444332774966764878608501171813320645929380172024167239716820831079290125095379068439212748888117598941524136428159633675673981802978616600058167488937798380562157936902535788948513585151443009840170928664272669260565240279454871002029679021205074963629312821345244354310398913369718417670069378310689331141751130563839827125249504141124441851986383309099116639214477185701721432659123877972108155353747784873478698271659076269274157240344214695800204641058004942336734432057915774280073752348884298588198768477662726079574069574300127580133343836267315013351708387336108584129310669414748891721830040384145161726381949607384497475034581738955923257790467042600877491010875913461635706268825461741390802838301176526819147725797065517868344374822800174457366802069330914971090184845806085318607407543370109303131624320585331974815215506047010426991397696780885107448229107941162095759193717582007508049355481765309711512161875251755377816885263111664846964598475707958583397242912080069040723098238257275487695166939698916614082288718065176213787627959454742115963778572748738250397244030147372278678804058805929285889959209092591634706150438694126788805402911035479946022204422095698659915862374847292998066319647438948703485962838299490573750526000948266427616538918292705083156374295078319145969882436043804278219720089503341672644073646894915522466723173953730083171454586076813218917121031541889333563756543337241739262896542165170186649998733278356461344911954949707029189690403864280376290088765513685401043299418399233736697020569161161595958467796826337137172207641109760413622233774665673592178721531827876969936808307506598760925806379481937038351635940098690447443047445116550534756472944859087663076178027660975469503347763188607356876501744335643137204661437705458440756764102085096436796510140575416840828946600937932691922924000074421606951954686271821918873475896018965620867402564955882022940515767460446802475962310952021492642657825362945216961698594964540325493722303632323324727142105910366329998066094019774280028136544435951946162160926030932768887183488587607768345809700344217134673534001068442660778586809345677994651227908197297255962460979732470571683696572467910316954834303887922407676945840699350328304767960647137799236048446843407136046839779150388360940992037454707363659187570723325496218599187091722214562891590340678512533564787590478930420812033157446803317857021341409337353636607951160690933939240832141930224103346607698439411225240894433232737899273191797512804090194406357447285022201905091588628503513027800769475791859679647558094428029829798087141717730343724795341733808138318993663738262134730698650467564084164953886021341225151313544087269654987589181396797546531884682922017415902487308416037379812855536237007501652895566172245279116385273838376843446226842214643234813768246562898361181239824736179438457671542182161997138581145830006868392592868143371165851136299232540895011198190059981490016920245295133401990629681579686590882813725932574776065634350729957798230015816457111413016823606953931370019345103618959244803972904117626232863514479418098217799630536310812050616384850498976697781834285790935670303956643013432370904615237617039009509679587650436730290984741208885631064466051822665868982791295202611783582527537730376825173279204105672113743427708480293357579574239587639959842663472824397656166965336197899533519561802626082604495978887362170358638988918398194785141249432545258445463010122130357439558972426920921300734915256921448702492501742143316035460921053088591793717396708301265402222008571545784305137560456465090301530303411332401743810680964585086720384201905880660891557177506736044144549020567405235962340066288409758057098737633474379384213912978204038940587199561454966676419302616925127381379448800699627787976606862355069625844388034636193740869272123177936070856572539635570600113871655644079960447636989082696321308211804408215881380854507846020285220422117131135853021598378541138356279306602848382986777366582863294263482978061629306204254192969193391253971814437547693672055773396560331883107557310202674855803143692429450863943345531189008151133773805565202873518467959787701098743980841526560812655812577524477683421472631177833541190404241930478808898915362142239170114200148120845700068227302163092424509850547093951449670685649292184408755914783167981665213703207976314544626768519665547620055993587962747554343581734236384397067372888556867185224416696196988631436238610758987706278940642363289762297194358393485543415935596044715584236192203588892066073254601528117515078870869458158769158849485412975018300834757852308243689379051007389184247434766900033129421827876396445579986505158711233001693454874616004153061635188173279702689109182507193710207997781486925386704688323952841189504448903816125581222310779409366767269341195986318574815389048757675708096754568807019739380865924457276847562075410365340882195463125220395332363641275606688401590603603835545648104202228402074831352023667781887081427613471668894536611237205415997110740912984612409150745035127181514423147104849040912286047824237661884276273754384991090547853067884214721248806473174189331959443748639751628385666515075764786137067151058596590248542133882547771501935899274667322122667741096528282284040134100252901712267880638249749806114481379947916919445696418179658228821543819503299350444633684477211358736100428437622441829313228466800148060208737306434740551496340207540633285248481230280548904124902521605914801954359293566750777477286028453171874244276113306534738423042978719649047777829031852707036430788632782649842736577376962163243149697391280870516723475002436466592860167875756512565409745707848661754519159120845435998008629587385341081327446004137144457628225873949353571962194319006222218022338707640621468706038868373346053359320153827239658910825825900837488001661343766657569472328306888807121394393399628779669860008642699443375763692601332284889079718744889948687766283692431974903604820697116581959348271753353202309017803468965723118910078597595564330800724764254646090886298053075305865680910775518849352456060094134434188969789237991325061545356874953690096202642270307285057377684547851559481726395555324353267780748320233980354295418030390529197606534435936119645744869184709048440512341851963476498609519947802545990636817055776914198920871578340182672435678274685226500313051840310129923314490466821274413367389872874088146454759017631343000991387119851545821184", 10);
	
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime - startTime;
	std::cout << "duration " << (duration / std::chrono::milliseconds(1)) << "ms\n";
}

void PerformanceTest::createPrime() {
	// RandomNumber Test
	ppvr::math::Random& rnd = ppvr::math::Random::getForLocalThread();
	for(int i = 0; i<100; i++) {
		//std::cout << ppvr::math::BigInt::randomNumber(65).toStringHex() << " \n";
		std::cout << "probablePrime: " << ppvr::math::SArbBigInt::probablePrime(1024, rnd).toStringDec() << " \n";
	}
}