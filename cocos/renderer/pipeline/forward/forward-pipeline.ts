import { Root } from "../../../core/root";
import { RenderPipeline } from "../../../pipeline/render-pipeline";

export class ForwardPipeline extends RenderPipeline {

    constructor(root: Root) {
        super(root);
    }

    public initialize(): boolean {
        
        return true;
    }

    public destroy(): void {
        this.destroyFlows();
    }
};
