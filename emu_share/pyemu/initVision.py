import torch, torchvision
import detectron2
# import some common libraries
import numpy as np
import cv2
import random
# import some common detectron2 utilities
from detectron2 import model_zoo
from detectron2.engine import DefaultPredictor
from detectron2.config import get_cfg
from detectron2.utils.visualizer import Visualizer
from detectron2.data import MetadataCatalog,DatasetCatalog
from detectron2.data.datasets import register_coco_instances
from detectron2.utils.visualizer import ColorMode
# import matplotlib.pyplot as plt
import os
import json
from detectron2.structures import BoxMode, Instances,Boxes
import time
from detectron2.modeling import build_model
from detectron2.checkpoint import DetectionCheckpointer
import rospy
import sys
import rospkg
rospack = rospkg.RosPack()
share_pkg = rospack.get_path('emu_share')
sys.path.append(share_pkg)
package_path = rospack.get_path('emu_core')
this_file = '/'.join(__file__.split("/")[0:-1])+'/'
config_path = this_file

def get_scrapble_dicts(json_dir,img_dir):
    json_file = os.path.join(json_dir, "valid.json")
    with open(json_file) as f:
        imgs_anns = json.load(f)
    dataset_dicts = []
    classes_list=['bottle','can','snack']
    for idx, v in enumerate(imgs_anns.values()):
        record = {}
        annos = v["regions"]
        if len(annos)!=0:
            filename = os.path.join(img_dir, v["filename"])
            height, width = cv2.imread(filename).shape[:2]

            record["file_name"] = filename
            record["image_id"] = idx
            record["height"] = height
            record["width"] = width


            objs = []
            
            for anno in annos:

                annoshape = anno["shape_attributes"]
                px = annoshape["all_points_x"]
                py = annoshape["all_points_y"]
                poly = [(x + 0.5, y + 0.5) for x, y in zip(px, py)]
                poly = [p for x in poly for p in x]
#                 if anno["region_attributes"]['classes']=='can':
#                     count+=1
#                 print(record["file_name"])
                obj = {
                    "bbox": [np.min(px), np.min(py), np.max(px), np.max(py)],
                    "bbox_mode": BoxMode.XYXY_ABS,
                    "segmentation": [poly],
                    "category_id": classes_list.index(anno["region_attributes"]["classes"]),
                    "iscrowd": 0
                }
                objs.append(obj)
            record["annotations"] = objs
            dataset_dicts.append(record)
        else:
#             print('here')
            pass
            
    return dataset_dicts
def initModel(testThresh=0.9,classNum = 3):
    if classNum == 3:
        DatasetCatalog.register("scrapble",lambda d=1: get_scrapble_dicts('./','./'))
        MetadataCatalog.get("scrapble").set(thing_classes=["bottle","can","snack"])
        cfg = get_cfg()
        cfg.merge_from_file(config_path+'/model/x101v14.yaml')
        cfg.DATASETS.TEST = ('scrapble',)
        cfg.MODEL.WEIGHTS = os.path.join(config_path+'/model', "x101v14.pth")
        cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = testThresh
        cfg.MODEL.DEVICE='cuda:0'
        # cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = 0.85
        rospy.logdebug("init Predictor..")
        print("init Predictor..")
        
        predictor = DefaultPredictor(cfg)
        # model = build_model(cfg)  # returns a torch.nn.Module
        # DetectionCheckpointer(model).load('./output/r50fpn_combine.pth')
        # model.train(False)
        rospy.logdebug("init complete")
        print("init complete")
        
        return predictor
    elif classNum == 6:
        register_coco_instances("6class", {}, ".", ".")
        MetadataCatalog.get("6class").thing_classes = ["bottle_top","bottle_side", "can_top","can_side","snack_top","snack_side"]
        cfg = get_cfg()
        cfg.merge_from_file(config_path+'/model/x101v2.yaml')
        cfg.DATASETS.TEST = ('scrapble',)
        cfg.MODEL.WEIGHTS = os.path.join(config_path+'/model', "x101v2.pth")
        cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = testThresh
        cfg.MODEL.DEVICE='cuda:0'
        # cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = 0.85
        rospy.logdebug("init Predictor..")
        print("init Predictor..")
        
        predictor = DefaultPredictor(cfg)
        # model = build_model(cfg)  # returns a torch.nn.Module
        # DetectionCheckpointer(model).load('./output/r50fpn_combine.pth')
        # model.train(False)
        rospy.logdebug("init complete")
        print("init complete")
        
        return predictor
def visualModel(frame,outputs,classNum,idx=None):
    if classNum == 3:
        if idx!= None:
            # print(outputs["instances"].pred_masks.shape)
            vis = Instances(image_size=(1128, 440))
            classes=[outputs['instances'].pred_classes[0].item()]
            scores=[outputs["instances"].scores[0].item()]
            masks=outputs["instances"].pred_masks[0].reshape(1,440,1128)
            boxes=outputs["instances"].pred_boxes[0]
            
            for i in idx[1:]:
                
                classes=classes+[outputs['instances'].pred_classes[i].item()]
                scores=scores+[outputs["instances"].scores[i].item()]
                
                masks=torch.cat((masks,outputs["instances"].pred_masks[i].reshape(1,440,1128)),dim=0)
                
                boxes=Boxes.cat((boxes,outputs["instances"].pred_boxes[i]))
                
            vis.set('pred_classes', classes)
            vis.set('scores', scores)
            vis.set('pred_masks', masks)
            vis.set('pred_boxes', boxes)
               
            
            v = Visualizer(frame[:,:,::-1], MetadataCatalog.get("scrapble"), scale=0.8,instance_mode=ColorMode.IMAGE_BW )
            v = v.draw_instance_predictions(vis.to("cpu"))
        # cv2.imwrite("./output.jpg",v.get_image()[:, :, ::-1])
            o_image = cv2.resize(v.get_image()[:, :, ::-1],(1128,440))
            return o_image
    # # MetadataCatalog.get(cfg.DATASETS.TEST[0]).set(thing_classes=["bottle","can","snack"])
        v = Visualizer(frame[:,:,::-1], MetadataCatalog.get("scrapble"), scale=0.8)
        v = v.draw_instance_predictions(outputs["instances"].to("cpu"))
    # cv2.imwrite("./output.jpg",v.get_image()[:, :, ::-1])
        o_image = cv2.resize(v.get_image()[:, :, ::-1],(1128,440))
        return o_image
    elif classNum == 6:
        # # MetadataCatalog.get(cfg.DATASETS.TEST[0]).set(thing_classes=["bottle","can","snack"])
        v = Visualizer(frame[:,:,::-1], MetadataCatalog.get("6class"), scale=0.8)
        v = v.draw_instance_predictions(outputs["instances"].to("cpu"))
    # cv2.imwrite("./output.jpg",v.get_image()[:, :, ::-1])
        o_image = cv2.resize(v.get_image()[:, :, ::-1],(1128,440))
        return o_image
