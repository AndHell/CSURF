// DO NOT EDIT! generated by ./autogen

#include "fp.h"

// 100 mults, 505 squarings
void fp_inv(fp *x)
{
  fp r0;
  r0 = *x; // 1
  fp r1;
  fp_sq2(&r1,&r0);
  fp r2;
  fp_mul3(&r2,&r0,&r1); // 3
  fp r3;
  fp_mul3(&r3,&r1,&r2); // 5
  fp r4;
  fp_mul3(&r4,&r1,&r3); // 7
  fp r5;
  fp_mul3(&r5,&r1,&r4); // 9
  fp r6;
  fp_mul3(&r6,&r1,&r5); // 11
  fp r7;
  fp_mul3(&r7,&r1,&r6); // 13
  fp r8;
  fp_mul3(&r8,&r1,&r7); // 15
  fp r9;
  fp_mul3(&r9,&r1,&r8); // 17
  fp r10;
  fp_mul3(&r10,&r1,&r9); // 19
  fp_mul2(&r10,&r1); // 21
  fp r11;
  fp_mul3(&r11,&r1,&r10); // 23
  fp r12;
  fp_mul3(&r12,&r1,&r11); // 25
  fp r13;
  fp_mul3(&r13,&r1,&r12); // 27
  fp r14;
  fp_mul3(&r14,&r1,&r13); // 29
  fp r15;
  fp_mul3(&r15,&r1,&r14); // 31
  fp r16;
  fp_mul3(&r16,&r1,&r15); // 33
  fp r17;
  fp_mul3(&r17,&r1,&r16); // 35
  fp_mul2(&r1,&r17); // 37
  fp r18;
  fp_mul3(&r18,&r13,&r1); // 64
  fp_sq1(&r18);
  fp_mul2(&r18,&r0); // 129
  fp_sq1_rep(&r18,5);
  fp_mul2(&r18,&r10); // 4149
  fp_sq1_rep(&r18,6);
  fp_mul2(&r18,&r4); // 265543
  fp_sq1_rep(&r18,8);
  fp_mul2(&r18,&r2); // 67979011
  fp_sq1_rep(&r18,6);
  fp_mul2(&r18,&r3); // 4350656709
  fp_sq1_rep(&r18,7);
  fp_mul2(&r18,&r6); // 556884058763
  fp_sq1_rep(&r18,5);
  fp_mul2(&r18,&r10); // 17820289880437
  fp_sq1_rep(&r18,6);
  fp_mul2(&r17,&r18); // 1140498552348003
  fp_sq1_rep(&r17,6);
  fp_mul2(&r17,&r1); // 72991907350272229
  fp_sq1_rep(&r17,6);
  fp_mul2(&r17,&r16); // 4671482070417422689
  fp_sq1_rep(&r17,7);
  fp_mul2(&r17,&r0); // 597949705013430104193
  fp_sq1_rep(&r17,9);
  fp_mul2(&r17,&r5); // 306150248966876213346825
  fp_sq1_rep(&r17,7);
  fp_mul2(&r17,&r13); // 39187231867760155308393627
  fp_sq1_rep(&r17,5);
  fp_mul2(&r17,&r6); // 1253991419768324969868596075
  fp_sq1_rep(&r17,5);
  fp_mul2(&r17,&r8); // 40127725432586399035795074415
  fp_sq1_rep(&r17,5);
  fp_mul2(&r17,&r7); // 1284087213842764769145442381293
  fp_sq1_rep(&r17,7);
  fp_mul2(&r17,&r1); // 164363163371873890450616624805541
  fp_sq1_rep(&r17,5);
  fp_mul2(&r17,&r13); // 5259621227899964494419731993777339
  fp_sq1_rep(&r17,6);
  fp_mul2(&r0,&r17); // 336615758585597727642862847601749697
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r1); // 21543408549478254569143222246511980645
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r12); // 1378778147166608292425166223776766761305
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r12); // 88241801418662930715210638321713072723545
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r10); // 5647475290794427565773480852589636654306901
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r11); // 722876837221686728419005549131473491751283351
  fp_sq1_rep(&r0,8);
  fp_mul2(&r0,&r4); // 185056470328751802475265420577657213888328537863
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r3); // 11843614101040115358416986916970061688853026423237
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r16); // 1515982604933134765877374325372167896173187382174369
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r13); // 194045773431441250032303913647637490710167984918319259
  fp_sq1_rep(&r0,13);
  fp_mul2(&r0,&r16); // 1589622975950366720264633660601446323897696132450871369761
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r5); // 50867935230411735048468277139246282364726276238427883832361
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r6); // 1627773927373175521550984868455881035671240839629692282635563
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r8); // 52088765675941616689631515790588193141479706868150153044338031
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r6); // 1666840501630131734068208505298822180527350619780804897418817003
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r9); // 53338896052164215490182672169562309776875219832985756717402144113
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r6); // 3413689347338509791371691018851987825720014069311088429913737223243
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r7); // 436952236459329253295576450413054441692161800871819319028958364575117
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r13); // 13982471566698536105458446413217742134149177627898218208926667666403771
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r6); // 447439090134353155374670285222967748292773684092742982685653365324920683
  fp_sq1_rep(&r0,9);
  fp_mul2(&r0,&r8); // 229088814148788815551831186034159487125900126255484407135054523046359389711
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r10); // 29323368211044968390634391812372414352115216160702004113286978949934001883029
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r11); // 1876695565506877977000601075991834518535373834284928263250366652795776120513879
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r11); // 60054258096220095264019234431738704593131962697117704424011732889464835856444151
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r9); // 3843472518158086096897231003631277093960445612615533083136750904925749494812425681
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r10); // 245982241162117510201422784232401734013468519207394117320752057915247967667995243605
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r5); // 7871431717187760326445529095436855488430992614636611754264065853287934965375847795369
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r15); // 251885814950008330446256931053979375629791763668371576136450107305213918892027129451839
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r8); // 16120692156800533148560443587454680040306672874775780872732806867533690809089736284917711
  fp_sq1_rep(&r0,10);
  fp_mul2(&r0,&r4); // 16507588768563745944125894233553592361274033023770399613678394232354499388507889955755736071
  fp_sq1_rep(&r0,8);
  fp_mul2(&r0,&r2); // 4225942724752318961696228923789719644486152454085222301101668923482751843458019828673468434179
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r3); // 270460334384148413548558651122542057247113757061454227270506811102896117981313269035101979787461
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r15); // 8654730700292749233553876835921345831907640225966535272656217955292675775402024609123263353198783
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r1); // 1107805529637471901894896234997932266484177948923716514899995898277462499251459149967777709209444261
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r6); // 70899553896798201721273359039867665054987388731117856953599737489757599952093385597937773389404432715
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r10); // 4537571449395084910161494978551530563519192878791542845030383199344486396933976678268017496921883693781
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r5); // 580809145522570868500671357254595912130456688485317484163889049516094258807549014818306239606001112803977
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r1); // 74343570626889071168085933728588276752698456126120637972977798338060065127366273896743198669568142438909093
  fp_sq1_rep(&r0,8);
  fp_mul2(&r0,&r6); // 19031954080483602219029999034518598848690804768286883321082316374543376672605766117566258859409444464360727819
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r15); // 609022530575475271008959969104595163158105752585180266274634123985388053523384515762120283501102222859543290239
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r4); // 38977441956830417344573438022694090442118768165451537041576583935064835425496609008775698144070542263010770575303
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r3); // 2494556285237146710052700033452421788295601162588898370660901371844149467231782976561644681220514704832689316819397
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r7); // 319303204510354778886745604281909988901836948811378991444595375596051131805668220999890519196225882218584232552882829
  fp_sq1_rep(&r0,9);
  fp_mul2(&r0,&r2); // 163483240709301646790013749392337914317740517791426043619632832305178179484502129151943945828467651695915127067076008451
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r6); // 5231463702697652697280439980554813258167696569325633395828250633765701743504068132862206266510964854269284066146432270443
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r12); // 669627353945299545251896317511016097045465160873681074666016081122009823168520721006362402113403501346468360466743330616729
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r1); // 42856150652499170896121364320705030210909770295915588778625029191808628682785326144407193735257824086173975069871573159470693
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r12); // 1371396820879973468675883658262560966749112649469298840916000934137876117849130436621030199528250370757567202235890341103062201
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r10); // 175538793072636603990513108257607803743886419132070251637248119569648143084688695887491865539616047456968601886193963661191961749
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r14); // 5617241378324371327696419464243449719804365412226248052391939826228740578710038268399739697267713518622995260358206837158142775997
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r9); // 179751724106379882486285422855790391033739693191239937676542074439319698518721224588791670312566832595935848331462618789060568831921
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r4); // 11504110342808312479122267062770585026159340364239356011298692764116460705198158373682666900004277286139894293213607602499876405242951
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r12); // 1472526123879463997327650184034634883348395566622637569446232673806906970265364271831381363200547492625906469531341773119984179871097753
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r14); // 47120835964142847914484805889108316267148658131924402222279445561821023048491656698604203622417519764029007025002936739839493755875128125
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r6); // 6031467003410284533054055153805864482195028240886323484451769031913090950206932057421338063669442529795712899200375902699455200752016400011
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r11); // 193006944109129105057729764921787663430240903708362351502456609021218910406621825837482818037422160953462812774412028886382566424064524800375
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r15); // 12352444422984262723694704954994410459535417837335190496157222977358010266023796853598900354395018301021620017562369848728484251140129587224031
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r16); // 790556443070992814316461117119642269410266741589452191754062270550912657025522998630329622681281171265383681123991670318622992072968293582338017
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r8); // 50595612356543540116253511495657105242257071461724940272259985315258410049633471912341095851601994960984555591935466900391871492669970789269633103
  fp_sq1_rep(&r0,6);
  fp_mul2(&r0,&r11); // 3238119190818786567440224735722054735504452573550396177424639060176538243176542202389830134502527677503011557883869881625079775530878130513256518615
  fp_sq1_rep(&r0,5);
  fp_mul2(&r0,&r4); // 103619814106201170158087191543105751536142482353612677677588449925649223781649350476474564304080885680096369852283836212002552816988100176424208595687
  fp_sq1_rep(&r0,7);
  fp_mul2(&r0,&r5); // 13263336205593749780235160517517536196626237741262422742731321590483100644051116860988744230922353367052335341092331035136326760574476822582298700247945
  fp_sq1_rep(&r0,8);
  fp_mul2(&r0,&r1); // 3395414068631999943740201092484489266336316861763180222139218327163673764877085916413118523116122461965397847319636744994899650707066066581068467263473957
  *x = r0;
}
